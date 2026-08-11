# Relay Manager Initialization Fix - Design Specification

## Problem Statement
The RelayManager module is never initialized because SystemManager::begin() omits to call Relays.begin(). This leaves all relay GPIO pins in their default state (likely inputs), causing no response when relay control functions are called.

## Root Cause
In SystemManager::begin(), all other modules (Lighting, Vehicle, BLE, WiFiInterface, Faults, OTA, Security) are initialized with their respective begin() calls, but Relays.begin() is missing. This results in:
- Relay GPIO pins never being configured as outputs
- No response from relay control functions (lock(), unlock(), ignitionOn(), etc.)
- The system appearing to have non-functional relays despite correct implementation

## Solution Overview
Add a single line to SystemManager::begin() to initialize the RelayManager module, matching the pattern used for all other modules.

## Specific Changes
In src/SystemManager.cpp, in the SystemManager::begin() function, add the following line:

```cpp
    // Core Modules
    Lighting.begin();
    Lighting.setScene(RGBScene::BOOT);

    Vehicle.begin();

    // ADD THIS LINE:
    Relays.begin();

    // Interface Modules
    BLE.begin();
    WiFiInterface.begin();

    // Utility Modules
    // Sensors.begin();  // TODO: Re-implement sensor management
    Faults.begin();
    OTA.begin();
    Security.begin();

    Log.info("System Ready");
```

## Design Rationale
1. **Consistency**: Follows the exact same pattern as other module initializations
2. **Appropriate categorization**: Places RelayManager in the "Core Modules" section alongside Lighting and Vehicle, which is fitting since relays are core vehicle control functions
3. **Minimal change**: Only adds one line, reducing risk of introducing errors
4. **Clear intent**: The comment helps future developers understand this is an intentional addition

## Impact Assessment
- **Positive**: Fixes the root cause of relay non-responsiveness
- **Risk**: Minimal - only adds one initialization line following existing patterns
- **Breaking changes**: None - all existing functionality preserved
- **Conventions**: Follows established patterns for module initialization

## Testing Considerations
1. **Functional verification**: After this change, relay functions (lock(), unlock(), ignitionOn(), etc.) should produce expected GPIO state changes
2. **Initialization timing**: Confirm that relay initialization occurs during system startup
3. **Integration testing**: Ensure no interference with other modules
4. **Comprehensive testing**: Test both direct relay functions and pulse-based functions (lock/unlock/starter)

## Related Files
- src/SystemManager.cpp - Contains the fix
- src/RelayManager.cpp - RelayManager implementation (unchanged)
- include/RelayManager.h - RelayManager interface (unchanged)
- include/Config.h - Contains pin definitions (unchanged)

## Implementation Notes
This fix assumes that the RelayManager implementation itself is correct for active-low relays (LOW=ON, HIGH=OFF), which has been verified through code review. The only missing piece was the initialization call.
