# L200 Nexus project summary

The standalone PlatformIO project is the authoritative ESP32 firmware for the separate `L200-Nexus-App` Flutter application.

## Current hardware

- Board family: ESP32-C6 / ESP32-C6-MINI-1 class controller
- PlatformIO compatibility target: `esp32-c6-devkitm-1`
- Firmware lineage: v2.4.0
- Active-low relays: lock GPIO18, unlock GPIO19, ignition GPIO20, starter GPIO21, headlights GPIO22
- RGB data: GPIO23 using the SM16703P single-wire driver; 12 addressable pixel groups; the strip is powered separately at 24V
- Vehicle inputs: GPIO0 battery ADC, GPIO1 engine-running, GPIO2 door trigger, GPIO3 ignition sense
- Keyestudio MMA8452Q: SDA GPIO6, SCL GPIO7
- MMA8452Q address: automatically detected at `0x1C` or `0x1D`
- Waterproof coolant probe: GPIO10 reserved for DS18B20 integration

Relay outputs initialize HIGH (inactive). The app supplies phone GPS; the ESP32 has no onboard GPS receiver.

The SM16703P protocol is RGB, 800kHz single-wire RZ. A 5V logic-level buffer is required between the 3.3V ESP32-C6 data output and the strip DIN input.

The BLE device name, service UUID and command/status characteristics remain unchanged so the existing Flutter app does not need a connection-layer rewrite.

See [PINOUT.md](PINOUT.md) and [WIRING.md](WIRING.md) for hardware connections.
