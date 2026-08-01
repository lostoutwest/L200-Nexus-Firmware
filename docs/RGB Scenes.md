# RGB Scenes

The RGB system uses a specific "Lighting Language" to communicate vehicle state to the user.

## Frozen Scene Map

| State | Effect | Colour | Meaning |
| :--- | :--- | :--- | :--- |
| `BOOT` | Sweep | White | System Initializing |
| `IDLE` | Static | Warm White | Ready / Standby |
| `BLE_ADVERTISING` | Breathe | Blue | Searching for Phone |
| `BLE_CONNECTED` | Static | Cyan | Handshake Complete |
| `UNLOCKING` | Sweep (L$\rightarrow$R) | Green | Unlocking Doors |
| `LOCKING` | Sweep (R$\rightarrow$L) | Red | Locking Doors |
| `IGNITION` | Fade In | Amber | Power On |
| `STARTING` | Chase | White | Engine Cranking |
| `ENGINE_RUNNING` | Heartbeat | Green | System Healthy |
| `LOW_BATTERY` | Pulse | Red | Low Voltage Alert |
| `OVERHEAT` | Pulse | Orange | Temp Critical |
| `ALARM` | Alternate | Red/Blue | Security Trigger |
| `OTA` | Rainbow | Multi | Firmware Updating |
| `FAULT` | Flash | Purple | System Error |

## Hardware
- **LED Strip**: WS2812B
- **Count**: 14 LEDs
- **Data Pin**: GPIO 5
