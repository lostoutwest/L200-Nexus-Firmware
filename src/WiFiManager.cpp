#include "../include/WiFiManager.h"
#include "../include/VehicleController.h"
#include "../include/VehicleState.h"
#include "../include/Logger.h"
#include "../include/Config.h"
#include <ArduinoJson.h>
#include <WebServer.h>
#include <WiFi.h>

WiFiManager WiFiInterface;

namespace {
const char* AP_SSID = WIFI_AP_NAME;
const char* AP_PASSWORD = WIFI_AP_PASSWORD;
const IPAddress AP_IP(192, 168, 4, 1);
const IPAddress AP_GATEWAY(192, 168, 4, 1);
const IPAddress AP_SUBNET(255, 255, 255, 0);

WebServer server(80);

String statusJson() {
    JsonDocument doc;
    VehicleState &state = Vehicle.state();

    doc["locked"]      = state.locked;
    doc["battery"]     = state.batteryVoltage;
    doc["water_temp"]  = state.coolantTemperature;
    doc["temp"]        = state.coolantTemperature;
    doc["engine"]      = state.engineRunning;
    doc["ignition"]    = state.ignition;
    doc["headlights"]  = state.headlights;
    doc["signal"]      = WiFi.softAPgetStationNum() > 0 ? -45 : 0;

    String output;
    serializeJson(doc, output);
    return output;
}

bool handleCommand(const String& command) {
    if (command == "LOCK") {
        return Vehicle.lock() != VehicleEvent::NONE;
    }
    if (command == "UNLOCK") {
        return Vehicle.unlock() != VehicleEvent::NONE;
    }
    if (command == "IGNITION_ON") {
        return Vehicle.ignitionOn() != VehicleEvent::NONE;
    }
    if (command == "IGNITION_OFF" || command == "STOP_ENGINE") {
        return Vehicle.ignitionOff() != VehicleEvent::NONE;
    }
    if (command == "START_ENGINE") {
        return Vehicle.startEngine() != VehicleEvent::NONE;
    }
    if (command == "HEADLIGHT_ON") {
        return Vehicle.headlights(true) != VehicleEvent::NONE;
    }
    if (command == "HEADLIGHT_OFF") {
        return Vehicle.headlights(false) != VehicleEvent::NONE;
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
    html += "<p>BLE Service: <strong>";
    html += SERVICE_UUID;
    html += "</strong></p>";
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
    WiFi.softAP(
        WIFI_AP_NAME,
        WIFI_AP_PASSWORD
    );

    server.on("/", HTTP_GET, sendHome);
    server.on("/api/status", HTTP_GET, sendStatus);
    server.on("/api/command", HTTP_POST, handleApiCommand);
    server.onNotFound([]() {
        server.send(404, "text/plain", "Not found");
    });
    server.begin();

    Vehicle.state().wifiConnected = true;
    Log.info("WiFi AP ready: " + String(AP_SSID));
    Log.info("WiFi AP IP: " + WiFi.softAPIP().toString());
}

void WiFiManager::update() {
    server.handleClient();
}
