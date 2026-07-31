#include "Logger.h"

void Logger::info(const char* msg) {
    print("INFO", msg);
}

void Logger::warn(const char* msg) {
    print("WARN", msg);
}

void Logger::error(const char* msg) {
    print("ERROR", msg);
}

void Logger::print(const char* level, const char* msg) {
    // Simple Serial prefix logging
    Serial.print("[" );
    Serial.print(level);
    Serial.print("] ");
    Serial.println(msg);
}
