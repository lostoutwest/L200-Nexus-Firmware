# L200 Nexus project summary

The standalone PlatformIO project is the authoritative ESP32 firmware for the separate `L200-Nexus-App` Flutter application.

## Current hardware

- Board: ESP32 NodeMCU-32S
- Firmware lineage: v2.3.0
- Active-low relays: lock GPIO16, unlock GPIO17, ignition GPIO18, starter GPIO19, headlights GPIO21
- RGB data: GPIO22
- Vehicle inputs: GPIO34 engine, GPIO35 battery, GPIO32 door, GPIO33 ignition
- Keyestudio MMA8452Q: SDA GPIO25, SCL GPIO26, INT1 GPIO27 reserved, INT2 GPIO13 reserved
- MMA8452Q address: automatically detected at `0x1C` or `0x1D`

Relay outputs initialize HIGH (inactive). The app supplies phone GPS; the ESP32 has no onboard GPS receiver.

See [PINOUT.md](PINOUT.md) and [WIRING.md](WIRING.md) for the hardware connections.
