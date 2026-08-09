#pragma once

enum class VehicleEvent
{
    NONE,

    LOCKED,
    UNLOCKED,

    IGNITION_ON,
    IGNITION_OFF,

    ENGINE_STARTED,
    ENGINE_STOPPED,

    HEADLIGHTS_ON,
    HEADLIGHTS_OFF
};