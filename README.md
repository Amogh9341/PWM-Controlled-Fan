# PWM-Controlled-Fan with Arduino

##  Problem Statement

Traditional fans run continuously or require manual control, often leading to energy waste. This project creates a smart solution: a **temperature-sensing fan controller** that turns ON/OFF or adjusts speed automatically based on room temperature. It uses an Arduino, servo motor (as a stand-in for a real fan), temperature sensor, buzzer, and an LCD to display system status.

---

## Design Overview

This project simulates a **table fan with a brain**. Based on real-time temperature input, the Arduino adjusts a servo to mimic fan speed (via angle). The system also:
- Displays temperature and fan speed on an LCD.
- Activates a buzzer at extreme temperature levels (freeze/hot).
- Uses PWM-style servo positioning for speed control.

---

## Features

- ✅ **Auto ON/OFF Control**: Fan activates above a threshold (10°C).
- ✅ **Speed Adjustment**: Servo-based fan speed changes linearly between 10°C–50°C.
- ✅ **Temperature Display**: 16x2 LCD shows temperature or alert text (e.g., "hot", "cool", "freeze").
- ✅ **Buzzer Alerts**:
  - 440 Hz for freezing (< 0°C)
  - 1000 Hz for cool zone (0°C–10°C)
  - Variable pitch for high heat (> 50°C)
- ✅ **PWM-Based Servo Control**: Acts as a quiet motor substitute.

---

## Hardware Used

| Component             | Purpose                               |
|----------------------|----------------------------------------|
| Arduino Uno R3 (U2)  | Main microcontroller                   |
| 16x2 LCD (U3)        | Display temperature & fan speed       |
| Temperature Sensor TMP36 (U1) | Reads ambient temperature             |
| Micro Servo Motor (SERVO1) | Simulates variable-speed fan          |
| Piezo Buzzer (PIEZO2)| Audio feedback (freeze/hot warnings)  |
| 1 kΩ Resistor (R1)   | LCD contrast or sensor protection     |
| 220 kΩ Resistor (R2) | Buzzer or LCD signal conditioning     |

---

## Working Logic

### Main Flow:
1. **Read temperature** from TMP36 via analog input.
2. **Convert to Celsius** using the formula:  
   \[`((V * 5V / 1024) - 0.5) * 100`\]
3. **Decide Fan Speed**:
  The system adjusts the fan speed (servo angle) based on the sensed temperature using the TMP36 sensor. The fan's speed varies smoothly between 0° and 90°, mapped from the temperature range 10°C to 50°C.
    
    |    Temperature Range |   Fan Action         |   Servo Angle |
    |----------------------|----------------------|----------------|
    | Below 10°C           | Fan OFF              | 0°             |
    | 10°C – 50°C          | Proportional speed   | 0° to 90°      |
    | Above 50°C           | Fan at max speed     | 90°            |

    The fan speed is expressed as a percentage of maximum (e.g., 45° → 50%). The LCD displays both temperature and speed. A piezo buzzer provides audible feedback at different temperature      zones (cool, freeze, hot).


4. **Buzzer Control**:
   - `< 0°C` → 440 Hz
   - `0°C–10°C` → 1000 Hz
   - `> 50°C` → 2000–4000 Hz (scaled)
   - Normal → buzzer off
5. **LCD Display**:
   - First line: temperature or status text
   - Second line: fan speed in %

---

## Key Concepts Used

- **Analog Input to Digital Control**: TMP36 reading mapped to servo PWM
- **Mapping & Thresholding**: `map()` + `if/else` to determine fan response
- **PWM Control**: `Servo.write(deg)` mimics variable fan speed
- **LCD Control**: `LiquidCrystal` library for data display
- **Sound Feedback**: `tone()` and `noTone()` to drive buzzer alerts

---

## Use Cases

-  **Smart Home Cooling**: Adaptive desk/table fan control
-  **Lab Equipment Protection**: Automatically cool circuits or enclosures
-  **Student Projects**: Beginner-friendly intro to embedded systems
-  **IoT Foundations**: Teaches sensor input → actuator response → feedback

---

## Concepts Used

-  Analog temperature reading using TMP36 and `analogRead()`.
-  PWM-based fan control via servo motor mapped to temperature.
-  Real-time feedback on 16x2 LCD using the LiquidCrystal library.
-  Buzzer alerts using `tone()` at different temperature levels.
-  Conditional logic (`if/else`) to map sensor input to actuator output.
-  Modular functions for clean conversion, mapping, and display.
-  Simulates a real-time embedded automation system.

