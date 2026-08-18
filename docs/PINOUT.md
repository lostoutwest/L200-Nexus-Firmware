# Pinout

## GPIO Assignments

| Function       | Pin | Description     |
| :---           | :---: | :---            |
| Lock           | GPIO16 | Active-low lock relay |
| Unlock         | GPIO17 | Active-low unlock relay |
| Ignition       | GPIO18 | Active-low ignition relay |
| Starter        | GPIO19 | Active-low starter relay |
| Headlights     | GPIO21 | Active-low headlights relay |
| RGB            | GPIO22 | SM16703P single-wire RGB data, 12 pixel groups |

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

The Feit strip is powered separately from the ESP32 at 24V. Connect the ESP32 ground to the strip power ground. Because the SM16703P DIN high-level threshold is based on its approximately 5V internal logic supply, use a 5V-powered 74AHCT125/74AHCT buffer for the GPIO22 data signal; do not feed 24V into GPIO22.
