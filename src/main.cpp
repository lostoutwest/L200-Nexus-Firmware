#include <Arduino.h>

#include "../include/Config.h"
#include "../include/SystemManager.h"
#include "../include/Logger.h"

//------------------------------------------------------
// Setup
//------------------------------------------------------

void setup()
{
    Serial.begin(115200);
    Log.begin();

    delay(1000);

    Log.info("");
    Log.info("==========================================");
    Log.info("        L200 NEXUS ACP");
    Log.info("        L200 Nexus ACP V2.3");
    Log.info("==========================================");
    Log.print("Firmware : ");
    Log.info(FW_VERSION);
    Log.info("");

    //--------------------------------------------------

    Log.info("[SYSTEM] Starting System Manager...");

    System.begin();

    //--------------------------------------------------

    Log.info("[SYSTEM] Ready.");
}

//------------------------------------------------------
// Main Loop
//------------------------------------------------------

void loop()
{
    System.update();

    delay(1);
}
