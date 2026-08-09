#include "../include/Logger.h"

void Logger::begin()
{
    Serial.begin(115200);
}

void Logger::banner()
{
    Log.info("==========================================");
    Log.info("        L200 NEXUS ACP");
    Log.info("        L200 Nexus ACP Automotive Control Platform");
    Log.info("==========================================");
}

void Logger::info(const String& text)
{
    Serial.println(text);
}

void Logger::warning(const String& text)
{
    Serial.print("[WARNING] ");
    Serial.println(text);
}

void Logger::error(const String& text)
{
    Serial.print("[ERROR] ");
    Serial.println(text);
}

void Logger::debug(const String& text)
{
    Serial.print("[DEBUG] ");
    Serial.println(text);
}

void Logger::print(const String& text)
{
    Serial.print(text);
}

void Logger::println(const String& text)
{
    Serial.println(text);
}