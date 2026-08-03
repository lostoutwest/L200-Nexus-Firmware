#pragma once

class VehicleControllerManager
{
public:

    void begin();

    void update();

    bool lock();

    bool unlock();

    bool ignitionOn();

    bool ignitionOff();

    bool startEngine();

    bool stopStarter();

    bool headlights(bool state);

    bool accessories(bool state);

    bool horn(bool state);

private:

    bool canStart() const;
};

extern VehicleControllerManager VehicleController;
