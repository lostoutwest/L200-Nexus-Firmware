# L200 NEXUS ACP Architecture

## Overview
The L200 NEXUS ACP (Automotive Control Platform) is designed as a modular, state-driven system for vehicle control and monitoring. It follows a strict separation of concerns to ensure reliability and maintainability.

## The Core Pattern: Brain, Memory, Muscle

### 1. Memory (`VehicleState`)
The `VehicleState` object is the single source of truth for the vehicle's current condition. 
- **No Logic**: It contains only data (booleans, floats, ints).
- **Centralized**: Every module reads from or writes to this state.
- **Predictable**: Prevents "state drift" where two modules disagree on whether the vehicle is locked.

### 2. Muscle (`RelayManager`, `RGBManager`)
These modules handle direct hardware interaction.
- **Hardware Abstraction**: They convert logical requests (e.g., `lock()`) into electrical signals (e.g., `GPIO 16 HIGH`).
- **No Decision Making**: They do not decide *when* to lock; they only know *how* to lock.

### 3. Brain (`VehicleManager`, `SystemManager`)
The brain modules orchestrate the flow between the memory and the muscle.
- **Request Handling**: They receive high-level requests (from BLE/WiFi).
- **Validation**: They check if a request is safe (e.g., don't allow `Starter` if `EngineRunning` is true).
- **Execution**: They command the "Muscle" and update the "Memory".

## Module Hierarchy
`SystemManager` (Root)
  ├─ `Logger` (System Voice)
  ├─ `VehicleManager` (Vehicle Brain)
  │   ├─ `RelayManager` (Hardware Muscle)
  │   └─ `VehicleState` (Vehicle Memory)
  ├─ `RGBManager` (Visual Feedback)
  ├─ `BLEManager` (External Interface)
  ├─ `WiFiManager` (Fallback Interface)
  ├─ `SensorManager` (Input Processor)
  ├─ `FaultManager` (Safety Monitor)
  ├─ `OTAManager` (Update Logic)
  └─ `SecurityManager` (Access Control)
