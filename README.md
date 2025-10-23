# 🤖 Arduino Distance LCD Meter, Joystick Controller & Communication Loop

This Arduino project combines three interactive modules into one integrated system:
1. **Ultrasonic Distance LCD Meter**  
2. **Joystick Controller for Servo/LED**  
3. **LED–Photoresistor Communication Loop**

---

## ⚙️ Overview

- Measures real-time **distance** using an HC-SR04 ultrasonic sensor and shows results on a **16×2 LCD**.  
- Reads joystick input to **control servo position** and **LED brightness**.  
- Implements a simple **optical communication loop** using an LED (transmitter) and photoresistor (receiver).  
- Displays **temperature and humidity** on the LCD via a **DHT11 sensor**.  

This single sketch merges all subsystems to demonstrate multi-sensor integration, I/O control, and data communication.

---

## 🧩 Components Used

| Component | Quantity | Function |
|------------|-----------|-----------|
| Arduino Uno | 1 | Main controller |
| DHT11 Sensor | 1 | Temperature & humidity |
| HC-SR04 Sensor | 1 | Distance measurement |
| 16×2 LCD (HD44780) | 1 | Display |
| Joystick Module | 1 | Control input |
| Servo Motor | 1 | Controlled by joystick X-axis |
| LED & Photoresistor | 1 pair | Optical communication |
| Jumper Wires, Breadboard | - | Circuit connections |

---

## 🗂 Project Structure

arduino-distance-lcd-joystick-comm/
├── arduino-distance-lcd-joystick-comm.ino
└── README.md

---

## 🧠 How to Use

1. **Connect** all components according to the pin definitions in the code.  
2. **Install required libraries:**
   - DHT sensor library (Adafruit)
   - Adafruit Unified Sensor
   - LiquidCrystal (built-in)
   - Servo (built-in)
3. **Upload the code** to your Arduino Uno using Arduino IDE.  
4. Watch live readings on the LCD and observe LED/servo response to joystick movements.  
5. Open Serial Monitor (9600 baud) to view communication debug messages.  

---

## ⚙️ Features by Module

### 🔹 Distance LCD Meter
- Displays distance (cm) measured by HC-SR04.  
- Uses moving average smoothing to reduce noise.  

### 🔹 Joystick Controller
- X-axis controls a servo motor (0–180°).  
- Y-axis controls LED brightness (PWM).  
- Joystick button can be used to reset or toggle behavior.  

### 🔹 Communication Loop
- Transmits text via LED flashes (TX).  
- Receives using photoresistor (RX).  
- Implements start/stop bits and basic framing.  

---

## 📚 Learning Outcomes

- Integrating multiple input/output devices in a single sketch.  
- Using interrupts, timing loops, and analog readings together.  
- Understanding serial-style communication via light signals.  
- Improving sensor calibration and data presentation.  

---

## 👨‍💻 Author

**Sahiru Imadith**  
2nd-Year BSc (Hons) Computer Science Student — UWE Bristol  
📧 [sahiruimadith200507@gmail.com](mailto:sahiruimadith200507@gmail.com)  
💼 [linkedin.com/in/sahiru-imadith-410845377](https://linkedin.com/in/sahiru-imadith-410845377)

---
⭐ *If you found this project useful, feel free to star the repo or connect with me!*
