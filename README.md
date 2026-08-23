#  ESP32 Ambulance Priority Traffic Light (ESP-NOW)

This project demonstrates an **IoT-based traffic management system** where an ambulance can wirelessly override traffic lights using ESP-NOW.

## Files
- **AmbulanceController/ambulance_controller.ino**  
  ESP32 with push buttons, used by ambulance driver to send priority signals.
  
- **TrafficLight/traffic_light.ino**  
  ESP32 at the traffic light pole, receives signals and controls LEDs (Red, Yellow, Green).

## Hardware
- 2 × ESP32 boards
- LEDs (Red, Yellow, Green)
- Push Buttons (for ambulance control)

## Features
- Normal traffic sequence: Red → Yellow → Green
- Ambulance override:
  - Case 1 → Force Green
  - Case 2 → Force Red
  - Case 3 → Force Yellow
- Communication via **ESP-NOW** (fast & connectionless).
