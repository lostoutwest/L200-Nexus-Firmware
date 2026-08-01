# Relay Mapping

The L200 Nexus ACP uses a rigid relay mapping to ensure hardware consistency.

## Pin Assignments (Rev A)

| Function | Pin | Logic | Description |
| :--- | :--- | :--- | :--- |
| Lock A | 16 | HIGH = Active | Door Lock Primary |
| Lock B | 17 | HIGH = Active | Door Lock Secondary |
| Ignition | 18 | HIGH = ON | Main Power Rail |
| Starter | 19 | HIGH = ON | Crank Signal |
| Headlights | 20 | HIGH = ON | Main Lighting |

## Lock Safety Logic
To prevent accidental triggers or faults, the locking system uses dual-relay verification:

- **LOCK**: Pin 16 == HIGH && Pin 17 == HIGH
- **UNLOCK**: Pin 16 == LOW && Pin 17 == LOW
- **FAULT**: Any mismatch (HIGH/LOW or LOW/HIGH) is flagged as a system fault.
