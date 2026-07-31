#include "SystemManager.h"

SystemManager System;

void setup()
{
    System.begin();
}

void loop()
{
    System.update();
}
