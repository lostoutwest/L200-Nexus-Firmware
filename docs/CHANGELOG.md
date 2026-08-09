# Changelog

## Release 2.3.0
- Repository cleanup and reorganization
- Serial logging replaced with centralized Logger system
- Headers moved to include directory
- Firmware renamed from Project Genesis to L200 Nexus ACP Automotive Control Platform
- Added secure BLE pairing placeholder
- Added encrypted command channel placeholder
- Added battery monitoring
- Added diagnostic mode
- Added engine runtime tracking
- Added fault logging
- Added OTA progress tracking
- Prepared for future CAN support

## Next Release (TODO)
- [ ] Secure WiFi AP credential storage: Replace hardcoded WIFI_AP_PASSWORD with ESP32 NVS storage
- [ ] Implement first-boot secure password generation and BLE configuration interface
- [ ] Add BLE characteristic for secure credential updates (ties to 'secure BLE pairing' feature)

## Release 2.1.0-a3 (Foundation Release)
- Architecture Freeze: L200 NEXUS ACP Version 2.1.
- Core Modular Framework implemented.
- All primary system managers added as compilable shell classes:
  - BLEManager, WiFiManager, SensorManager, FaultManager, OTAManager, SecurityManager.
- Formal Architecture documentation created in /docs.
- Relay mapping and RGB scene language frozen.

## Release 2.1.0-a2
- Vehicle core architecture implemented.
- VehicleState, RelayManager, and VehicleManager added.

## Release 2.1.0-a1
- Project restarted using PlatformIO.
- Initial system framework implemented.
- Logger and System Manager added.
