#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger {
public:
    void info(const char* msg);
    void warn(const char* msg);
    void error(const char* msg);
private:
    void print(const char* level, const char* msg);
};

#endif // LOGGER_H