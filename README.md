# 🚗 Voice Controlled Car with Obstacle Detection and Live Video Monitoring

## 📌 Project Overview

This project presents a smart robotic vehicle that can be controlled using voice commands through Bluetooth while simultaneously providing live video streaming using an ESP32-CAM module. The vehicle is equipped with multiple ultrasonic sensors to detect obstacles and automatically stop to prevent collisions. A buzzer alerts the user whenever an obstacle is detected.

The project combines Embedded Systems, IoT, Wireless Communication, and Robotics concepts into a single intelligent vehicle.

---

## ✨ Features

- 🎤 Voice-controlled movement using Bluetooth
- 📷 Live video monitoring using ESP32-CAM
- 🚧 Automatic front and rear obstacle detection
- 🔊 Buzzer alert for nearby obstacles
- 🛑 Automatic emergency stop
- ⚡ Adjustable motor speed
- 📡 Wireless control using HC-05 Bluetooth Module

---

## 🛠 Hardware Components

- Arduino UNO
- ESP32-CAM
- HC-05 Bluetooth Module
- L298N Motor Driver
- HC-SR04 Ultrasonic Sensors (3)
- Passive Buzzer
- DC Motors
- Robot Chassis
- Battery Pack

---

## 💻 Software Used

- Arduino IDE
- Embedded C++
- ESP32 Camera Library
- Wi-Fi Library
- Bluetooth Communication

---

## ⚙ Working Principle

1. Voice commands are sent from a mobile phone through the HC-05 Bluetooth module.
2. Arduino UNO receives the commands and controls the motors.
3. Three ultrasonic sensors continuously monitor obstacles.
4. If an obstacle is detected within the safety distance, the vehicle stops automatically and activates the buzzer.
5. The ESP32-CAM streams live video over Wi-Fi, allowing remote monitoring through a web browser.

---

## 📂 Project Structure

```
Arduino_UNO/
    voice_controlled_car/

ESP32_CAM/
    esp32_cam_stream/

Circuit_Diagram/

Images/

Report/
```

---

## 🚀 Future Enhancements

- Mobile Application Control
- Autonomous Navigation
- GPS Tracking
- AI-based Object Detection
- Night Vision Camera
- Cloud Video Streaming

---

## 👨‍💻 Team

This project was developed by a team of **4 members** as part of our engineering coursework.

---

## 👤 Author

**Yashwanth H S**

Electronics and Communication Engineering  
Sir M. Visvesvaraya Institute of Technology

---

## ⭐ GitHub

If you found this project useful, feel free to star the repository.
