#include "WiFiManager.h"
#include "VehicleManager.h"
#include "VehicleState.h"
#include "Logger.h"
#include <ArduinoJson.h>
#include <WebServer.h>
#include <WiFi.h>

WiFiManager WiFiInterface;

namespace {
const char* AP_SSID = "L200 Sport";
const char* AP_PASSWORD = "sport1981";
const IPAddress AP_IP(192, 168, 4, 1);
const IPAddress AP_GATEWAY(192, 168, 4, 1);
const IPAddress AP_SUBNET(255, 255, 255, 0);

WebServer server(80);

String statusJson() {
    JsonDocument doc;
    doc["locked"] = Vehicle.locked;
    doc["battery"] = Vehicle.batteryVoltage;
    doc["water_temp"] = Vehicle.coolantTemperature;
    doc["temp"] = Vehicle.coolantTemperature;
    doc["engine"] = Vehicle.engineRunning;
    doc["ignition"] = Vehicle.ignition;
    doc["headlights"] = Vehicle.headlights;
    doc["signal"] = WiFi.softAPgetStationNum() > 0 ? -45 : 0;

    String output;
    serializeJson(doc, output);
    return output;
}

bool handleCommand(const String& command) {
    if (command == "LOCK") {
        return VehicleController.lock();
    }
    if (command == "UNLOCK") {
        return VehicleController.unlock();
    }
    if (command == "IGNITION_ON") {
        return VehicleController.ignitionOn();
    }
    if (command == "IGNITION_OFF" || command == "STOP_ENGINE") {
        return VehicleController.ignitionOff();
    }
    if (command == "START_ENGINE") {
        return VehicleController.startEngine();
    }
    if (command == "HEADLIGHT_ON") {
        return VehicleController.headlights(true);
    }
    if (command == "HEADLIGHT_OFF") {
        return VehicleController.headlights(false);
    }
    return false;
}

void sendStatus() {
    server.send(200, "application/json", statusJson());
}

void sendHome() {
    String html = "<html><head><title>L200_Nexus_ACP</title></head><body>";
    html += "<h1>L200_Nexus_ACP</h1>";
    html += "<p>WiFi AP ready: " + String(AP_SSID) + "</p>";
    html += "<p>BLE Device: <strong>L200_Nexus_ACP</strong></p>";
    html += "<p>BLE Service: <strong>7A5E1000-5D84-C7B9-F0A8-E6D0A010001</strong></p>";
    html += "<p>API endpoints:</p>";
    html += "<ul>";
    html += "<li><code>GET /api/status</code></li>";
    html += "<li><code>POST /api/command</code> with JSON <code>{ &quot;command&quot;:&quot;LOCK&quot; }</code></li>";
    html += "</ul>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void handleApiCommand() {
    JsonDocument doc;
    const DeserializationError error = deserializeJson(doc, server.arg("plain"));
    if (error || !doc["command"].is<String>()) {
        server.send(400, "application/json", "{\"ok\":false,\"msg\":\"missing command\"}");
        return;
    }

    String command = doc["command"];
    command.trim();
    command.toUpperCase();

    const bool ok = handleCommand(command);
    if (!ok) {
        server.send(400, "application/json", "{\"ok\":false,\"msg\":\"unknown or rejected command\"}");
        return;
    }

    sendStatus();
}
}

void WiFiManager::begin() {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(AP_IP, AP_GATEWAY, AP_SUBNET);
    WiFi.softAP(AP_SSID, AP_PASSWORD);

    server.on("/", HTTP_GET, sendHome);
    server.on("/api/status", HTTP_GET, sendStatus);
    server.on("/api/command", HTTP_POST, handleApiCommand);
    server.onNotFound([]() {
        server.send(404, "text/plain", "Not found");
    });
    server.begin();

    Vehicle.wifiConnected = true;
    Log.info("WiFi AP ready: " + String(AP_SSID));
    Log.info("WiFi AP IP: " + WiFi.softAPIP().toString());
}

void WiFiManager::update() {
    server.handleClient();
}
