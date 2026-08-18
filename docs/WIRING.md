# NEXUS MMA8452Q wiring

The firmware uses the following ESP32 NodeMCU-32S connections:

| MMA8452Q | ESP32 | Purpose |
|---|---:|---|
| GND | GND | Ground |
| VCC | 3.3V | Sensor supply |
| SDA | GPIO25 | I2C data |
| SCL | GPIO26 | I2C clock |
| INT1 | GPIO27 | Reserved for motion/jolt interrupts |
| INT2 | GPIO13 | Reserved for orientation/tilt interrupts |

The initial implementation leaves INT1 and INT2 disconnected and reads X/Y/Z over I2C. The sensor is detected at address 0x1C or 0x1D.

## Operating modes

- **LOCKED**: movement and tilt are monitored; the first tamper event latches tamperDetected and selects the RGB ALARM scene.
- **UNLOCKED**: telemetry remains active, but movement does not trigger the security alarm.
- **DRIVING**: selected while ignition or engine state is active; acceleration, pitch, roll, impact/movement telemetry remain available without security alarming.

The RGB data line is GPIO22.
