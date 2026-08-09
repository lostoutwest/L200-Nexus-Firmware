#pragma once

#include <Arduino.h>

class SecurityManager {
public:
    void begin();
    void update();
};

extern SecurityManager Security;
