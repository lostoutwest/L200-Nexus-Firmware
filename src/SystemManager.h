#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "Logger.h"
#include "version.h"

class SystemManager {
public:
    SystemManager();
    void begin();
    void update();
private:
    Logger logger;
    // Add any subsystem members here
};

#endif // SYSTEMMANAGER_H