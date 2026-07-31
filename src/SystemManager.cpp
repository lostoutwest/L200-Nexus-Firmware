#include "SystemManager.h"
#include <Arduino.h>

SystemManager::SystemManager() {
    // Constructor can initialize subsystems if needed
}

void SystemManager::begin() {
    // Print boot screen with version and codename
    logger.info("========================================");
    logger.info("L200 NEXUS ACP");
    logger.info("");
    logger.info("Firmware " FIRMWARE_VERSION);
    logger.info("Codename: " FIRMWARE_CODENAME);
    logger.info("Hardware: REV A");
    logger.info("Board: NEXUS-A01");
    logger.info("Ready");
    logger.info("========================================");
    // Initialize other subsystems here
}

void SystemManager::update() {
    // Placeholder for main loop updates. Currently does nothing.
    // Future modules will be called here.
}
