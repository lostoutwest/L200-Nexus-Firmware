# L200 Nexus ACP Firmware

ESP32-based Automotive Control Platform (ACP) for the 1981 Mitsubishi L200 Sport.

The goal of this project is to provide a modern Bluetooth LE vehicle controller with support for remote locking, ignition control, engine starting, lighting, OTA updates and a companion Flutter application.

---

## Features

### Bluetooth Low Energy (BLE)

- Stable BLE advertising
- Custom GATT service
- Vehicle command interface
- Live vehicle status notifications

### Vehicle Control

- Lock
- Unlock
- Ignition On / Off
- Engine Start
- Headlights

### RGB Status System

- Boot animation
- BLE advertising
- Connected indication
- Lock / Unlock effects
- Engine running
- Fault indication

### Connectivity

- Wi-Fi Access Point
- HTTP API
- OTA firmware updates

### Security

- Command validation
- Expandable authentication framework

---

# Hardware

Current development platform

- ESP32 NodeMCU-32S
- 4-Channel Relay Module
- 12V Vehicle Electrical System

Current hardware configuration: active-low relay outputs on GPIO16/17/18/19/21, RGB data on GPIO22, vehicle inputs on GPIO34/35/32/33, and a Keyestudio MMA8452Q tilt sensor on I²C GPIO25/26 at address `0x1C` or `0x1D`.

---

# Repository Structure

```text
include/
lib/
src/
docs/
hardware/
platformio.ini
```

---

# Companion Application

The Flutter application is maintained separately:

**L200-Nexus-App**

---

# Documentation

- Architecture
- BLE API
- Relay Mapping
- RGB Scenes
- Wiring
- Pinout
- Project summary

---

# Development Status

Current Version

**v2.3.0**

Working

- BLE
- Vehicle Controller
- Relay Manager
- Wi-Fi AP
- OTA Framework
- RGB Manager

Currently Improving

- Relay hardware integration
- BLE authentication
- Vehicle diagnostics
- Battery monitoring

---

# Roadmap

- Secure BLE pairing
- OTA improvements
- Diagnostic Trouble Codes
- CAN expansion
- Mobile App enhancements
- PCB controller design

---

# License

MIT License

---
