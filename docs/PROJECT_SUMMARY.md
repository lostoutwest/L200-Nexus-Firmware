# L200 Nexus project summary

The standalone PlatformIO project is the authoritative ESP32 firmware for the separate `L200-Nexus-App` Flutter application.

## Current hardware

- Board: ESP32 NodeMCU-32S
- Firmware lineage: v2.3.0
- Active-low relays: lock GPIO16, unlock GPIO17, ignition GPIO18, starter GPIO19, headlights GPIO21
- RGB data: GPIO22 using the SM16703P single-wire driver; the strip is powered separately at 24V
- Vehicle inputs: GPIO34 engine, GPIO35 battery, GPIO32 door, GPIO33 ignition
- Keyestudio MMA8452Q: SDA GPIO25, SCL GPIO26, INT1 GPIO27 reserved, INT2 GPIO13 reserved
- MMA8452Q address: automatically detected at `0x1C` or `0x1D`

Relay outputs initialize HIGH (inactive). The app supplies phone GPS; the ESP32 has no onboard GPS receiver.

The SM16703P protocol is RGB, 800kHz single-wire RZ. A 5V logic-level buffer is required between the 3.3V ESP32 data output and the strip DIN input. The configured LED group count remains `RGB_LED_COUNT` until the physical strip grouping is confirmed.

See [PINOUT.md](PINOUT.md) and [WIRING.md](WIRING.md) for the hardware connections.
