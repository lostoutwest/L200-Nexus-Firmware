# L200 Nexus Firmware

Automotive Control Platform (ACP)
Designed for the 1981 Mitsubishi L200 Sport.

**Project Codename:** GENESIS
**Current Release:** 2.1.0-a3 (Foundation Release)

---

## 🚀 Project Status
`Status: 🚧 Active Development / Architecture Frozen`

By treating this as a long-term engineering project, we ensure the firmware, hardware, and app evolve naturally and maintain a professional, cohesive standard.

## 📦 Release Roadmap
- **2.1.0-a1**: Core Boot & Logging
- **2.1.0-a2**: Vehicle Core (BCM)
- **2.1.0-a3**: Foundation Release (All Core Managers)
- **2.1.0-a4**: BLE Integration
- **2.1.0-beta**: Flutter App Integration
- **Version 2.1**: Final Release Candidate

## 🛠 Hardware Architecture
The project is designed for an ESP32-S3 based custom PCB featuring:
- USB-C Programming/Power
- Dual-Relay Lock Safety Logic
- WS2812B RGB Animation Engine
- Sensor Input Array (Voltage, Temp, Pressure)
- CAN Bus Header

## 📂 Documentation
Detailed specifications are located in the `docs/` directory:
- [Architecture](docs/Architecture.md) - The "Brain, Memory, Muscle" pattern.
- [Relay Mapping](docs/Relay Mapping.md) - Hardware pin assignments.
- [RGB Scenes](docs/RGB Scenes.md) - The lighting language.

---
Developed for the 1981 Mitsubishi L200 Sport.
