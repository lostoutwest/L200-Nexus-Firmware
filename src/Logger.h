#pragma once

#include <Arduino.h>

class Logger
{
public:

    void begin();

    void banner();

    void info(const String& text);

    void warning(const String& text);

    void error(const String& text);

    void debug(const String& text);
};

extern Logger Log;
