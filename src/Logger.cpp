#include "Logger.h"

#include "../include/version.h"

Logger Log;

void Logger::begin()
{
    Serial.println();
}

void Logger::banner()
{
    Serial.println("==========================================");
    Serial.println("        L200 NEXUS ACP");
    Serial.println("        Project Genesis");
    Serial.println("==========================================");

    Serial.print("Firmware : ");
    Serial.println(FW_VERSION);

    Serial.print("Hardware : ");
    Serial.println(HW_REVISION);

    Serial.println();
}

void Logger::info(const String& text)
{
    Serial.print("[INFO ] ");
    Serial.println(text);
}

void Logger::warning(const String& text)
{
    Serial.print("[WARN ] ");
    Serial.println(text);
}

void Logger::error(const String& text)
{
    Serial.print("[ERROR] ");
    Serial.println(text);
}

void Logger::debug(const String& text)
{
    Serial.print("[DEBUG ] ");
    Serial.println(text);
}
