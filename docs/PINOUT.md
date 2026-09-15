# Pinout

## ESP32-C6 GPIO assignments

| Function | Pin | Description |
| :--- | :---: | :--- |
| Lock | GPIO18 | Active-low lock relay |
| Unlock | GPIO19 | Active-low unlock relay |
| Ignition | GPIO20 | Active-low ignition relay |
| Starter | GPIO21 | Active-low starter relay |
| Headlights | GPIO22 | Active-low headlights relay |
| RGB | GPIO23 | SM16703P single-wire RGB data, 12 pixel groups |

## Vehicle inputs

| Function | Pin | Notes |
| :--- | :---: | :--- |
| Battery sense | GPIO0 | ADC input. Must be conditioned to 0-3.3V maximum |
| Engine running | GPIO1 | Digital/pulse input through appropriate conditioning |
| Door trigger | GPIO2 | Digital input |
| Ignition input | GPIO3 | 12V ignition sense through optocoupler/conditioning |

## MMA8452Q tilt sensor

| Signal | ESP32-C6 pin | Notes |
| :--- | :---: | :--- |
| SDA | GPIO6 | I²C data |
| SCL | GPIO7 | I²C clock |
| I²C address | `0x1C` or `0x1D` | Detected automatically |

## Reserved sensor pin

| Function | Pin | Notes |
| :--- | :---: | :--- |
| Waterproof coolant probe | GPIO10 | Reserved for DS18B20 data |

Relay outputs are active-low and initialize HIGH (inactive).

GPIO4, GPIO5, GPIO8, GPIO9 and GPIO15 are intentionally not used for vehicle control outputs because they have ESP32-C6 boot/strapping roles. GPIO12 and GPIO13 are also kept free for native USB Serial/JTAG use.

The Feit/SM16703P strip remains separately powered at 24V. Connect controller ground to strip power ground and use the existing 5V-powered 74AHCT125 level buffer between the 3.3V ESP32-C6 RGB data output and strip DIN. Never feed 24V into an ESP32 GPIO.
