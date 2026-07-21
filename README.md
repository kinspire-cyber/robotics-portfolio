# 🤖 02 — Embedded Systems & Robotics Projects

> **Arduino, sensors, microcontrollers, and IoT prototypes.**

This folder is a portfolio of hardware projects — beginner-to-advanced, each with code, wiring, and documentation.

---

## 📁 Projects

| Project | Description | Status |
|---------|-------------|--------|
| [Binary Converter & Display](./) | Arduino reads decimal → displays binary on 8 LEDs | 📝 Documented |
| [Intelligent Water Tank Monitor](./IntelligentWaterTankMonitor/) | Arduino monitors water level and controls pump to prevent overflow | ✅ Completed |
| _Line-Following Robot_ | _IR sensor array + motor control_ | 🔜 Planned |
| _Obstacle Avoidance Bot_ | _HC-SR04 ultrasonic + servo_ | 🔜 Planned |
| _Smart Home IoT_ | _Relay control + Python backend_ | 🔜 Planned |

---

## 🛠️ Tech Stack

- **Boards:** Arduino Uno/Nano, ESP32 (future)
- **Languages:** C/C++ (Arduino), Python (serial bridge)
- **Tools:** Arduino IDE, Tinkercad, Wokwi, Serial Monitor
- **Hardware:** LEDs, sensors, motors, servos, breadboards

---

## 📝 Project README Template

Copy this into every new project you add:

````markdown
# 🔧 Project Name

> One-line tagline.

![Arduino](https://img.shields.io/badge/Arduino-Uno-00979D.svg)
![Status](https://img.shields.io/badge/Status-Prototype-orange.svg)

---

## 🎯 What It Does
- Bullet 1
- Bullet 2

## 🧰 Components Needed
- Arduino Uno
- 8 LEDs
- 8 × 220Ω resistors
- Breadboard + jumper wires

## 🔌 Wiring Diagram
_Add Fritzing diagram or pin table_

## 💻 Code
_Paste .ino code with comments_

## ▶️ How to Run
1. Connect Arduino via USB
2. Open `.ino` in Arduino IDE
3. Upload sketch
4. Open Serial Monitor (9600 baud)

## 📸 Demo
_Add photo or GIF of working circuit_

## 🗺️ Roadmap
- [ ] Add feature
- [ ] Add feature

## 👨‍💻 Author
Kingsley Onyema — [kinspiretech](https://youtube.com/@kinspiretech)
````

---

## 🚀 When This Becomes a GitHub Repo

```bash
cd 02_Embedded_Robotics_Projects
git init
git add .
git commit -m "feat: initialize robotics portfolio"
git branch -M main
git remote add origin https://github.com/<kinspire-cyber>/robotics-portfolio.git
git push -u origin main
```

---

Made with ❤️ by Kingsley Onyema
