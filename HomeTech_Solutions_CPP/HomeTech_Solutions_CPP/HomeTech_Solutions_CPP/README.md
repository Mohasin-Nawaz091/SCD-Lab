# HomeTech Solutions – Smart Home OOP System (C++)

## Overview

This is a complete console-based smart-home management system written in **C++** using Object-Oriented Programming.

### Features

- **Smart Lights**
  - Turn ON/OFF
  - Set brightness from 0–100%
- **Smart Thermostats**
  - Set room temperature
- **Smart Door Locks**
  - Lock/unlock
  - Record who unlocked the door
- Add devices
- Control devices
- View all devices
- Remove devices
- Automatic file persistence
- Auto-Mode
  - Temperature **above 25°C** → all lights turn ON
  - Temperature **below 18°C** → all lights turn OFF
  - Temperature **18°C to 25°C** → lights remain unchanged
- Invalid input is handled without crashing
- Private member variables with public getters/setters
- Inheritance and polymorphism
- No external libraries are required

## Files

```text
HomeTech_Solutions_CPP/
├── main.cpp
├── README.md
├── devices.txt
└── screenshots/
    ├── 01_auto_mode_and_devices.png
    ├── 02_persistence_after_restart.png
    └── 03_saved_device_data.png
```

## Requirements

Any standard C++ compiler supporting **C++17 or newer**.

Examples:
- GCC / MinGW
- Clang
- Visual Studio
- Code::Blocks
- Dev-C++

## Compile and Run

### GCC / MinGW

Open Command Prompt or Terminal in the project folder:

```bash
g++ -std=c++17 -Wall -Wextra -o HomeTech main.cpp
```

Then run:

**Windows**
```bash
HomeTech.exe
```

**Linux/macOS**
```bash
./HomeTech
```

### Visual Studio

Create a C++ Console project, add `main.cpp`, and build/run the project.

## Data Persistence

The program automatically saves devices in:

```text
devices.txt
```

The file is created in the same directory as the executable when the program first saves data.

When the application is closed and opened again, it loads the previously saved devices.

## Suggested Test

1. Add a Smart Light:
   - ID: `L1`
   - Name: `Living Room Light`
2. Add another Smart Light:
   - ID: `L2`
   - Name: `Bedroom Light`
3. Add a thermostat:
   - ID: `T1`
   - Name: `Main Thermostat`
   - Temperature: `22`
4. Add a door lock:
   - ID: `D1`
   - Name: `Front Door`
5. Set `L1` brightness to `50%`.
6. Turn `L2` ON.
7. Unlock `D1` and enter a person's name.
8. Set `T1` to `27°C`.
   - All lights should automatically turn ON.
9. Set `T1` to `17°C`.
   - All lights should automatically turn OFF.
10. Select **View All Devices**.
11. Exit.
12. Start the program again and select **View All Devices**.
   - The devices should still be present.

## OOP Concepts Used

### Encapsulation
Device data is stored in private member variables and accessed through getters/setters.

### Inheritance
`SmartLight`, `SmartThermostat`, and `SmartDoorLock` inherit from `SmartDevice`.

### Polymorphism
The `SmartDevice` base class uses virtual functions such as:

```cpp
virtual void display() const = 0;
virtual string serialize() const = 0;
```

This allows the `SmartHome` class to manage different device types through base-class pointers.

### Abstraction
Common device behavior is defined in the abstract `SmartDevice` class.

### Composition
`SmartHome` manages a collection of smart devices using `vector<unique_ptr<SmartDevice>>`.

## Important Note

The program uses a simple text file (`devices.txt`) rather than an external database so that the project remains easy to compile and run on almost any computer.
