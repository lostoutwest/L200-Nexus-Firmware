# BLE API

The L200 Nexus ACP exposes the following BLE commands for vehicle control:

## Commands

### LOCK
Locks the vehicle doors.
- **Request**: Send string `"LOCK"`
- **Response**: None (status notified via BLE)
- **Example**: 
  ```json
  // Send: "LOCK"
  ```

### UNLOCK
Unlocks the vehicle doors.
- **Request**: Send string `"UNLOCK"`
- **Response**: None (status notified via BLE)
- **Example**: 
  ```json
  // Send: "UNLOCK"
  ```

### IGNITION_ON
Turns ignition on (powers vehicle electronics).
- **Request**: Send string `"IGNITION_ON"`
- **Response**: None (status notified via BLE)
- **Example**: 
  ```json
  // Send: "IGNITION_ON"
  ```

### IGNITION_OFF
Turns ignition off.
- **Request**: Send string `"IGNITION_OFF"`
- **Response**: None (status notified via BLE)
- **Example**: 
  ```json
  // Send: "IGNITION_OFF"
  ```

### START_ENGINE
Starts the vehicle engine.
- **Request**: Send string `"START_ENGINE"`
- **Response**: None (status notified via BLE)
- **Example**: 
  ```json
  // Send: "START_ENGINE"
  ```

### STATUS
Requests current vehicle status.
- **Request**: Send string `"STATUS"`
- **Response**: JSON object with vehicle state
- **Example Response**:
  ```json
  {
    "locked": true,
    "battery": 12.6,
    "water_temp": 20.0,
    "temp": 20.0,
    "engine": false,
    "ignition": false,
    "headlights": false,
    "signal": 0
  }
  ```