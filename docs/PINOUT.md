# Pinout

## GPIO Assignments

| Function       | Pin | Description     |
| :---           | :---: | :---            |
| Lock           | GPIO16 | Active-low lock relay |
| Unlock         | GPIO17 | Active-low unlock relay |
| Ignition       | GPIO18 | Active-low ignition relay |
| Starter        | GPIO19 | Active-low starter relay |
| Headlights     | GPIO21 | Active-low headlights relay |
| RGB            | GPIO22 | WS2812B RGB data |

## Vehicle inputs

| Function | Pin |
| :--- | :---: |
| Engine running | GPIO34 |
| Battery sense | GPIO35 |
| Door trigger | GPIO32 |
| Ignition input | GPIO33 |

## MMA8452Q tilt sensor

| Signal | ESP32 pin | Notes |
| :--- | :---: | :--- |
| SDA | GPIO25 | I²C data |
| SCL | GPIO26 | I²C clock |
| INT1 | GPIO27 | Reserved; not currently connected |
| INT2 | GPIO13 | Reserved; not currently connected |
| I²C address | `0x1C` or `0x1D` | Detected automatically |

Relay outputs are active-low and initialize HIGH (inactive).
