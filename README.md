# SafeDrive – IoT Based Drunk Driving Prevention System

SafeDrive is an IoT-based safety system designed to prevent drunk driving by
detecting alcohol levels in a driver’s breath and taking automatic preventive
actions. The system integrates hardware sensors with cloud connectivity and
a web-based monitoring dashboard for real-time supervision by authorities.

---

## 🚗 Problem Statement
Drunk driving is one of the major causes of road accidents worldwide.
Traditional methods detect intoxication only after violations occur.
SafeDrive aims to prevent such incidents proactively using IoT technology.

---

## 🛠️ System Components

### Hardware
- ESP32 Microcontroller
- MQ-3 Alcohol Sensor
- NEO-6M GPS Module
- L298N Motor Driver
- Gear Motors
- Buzzer
- Battery

### Software
- Arduino IDE (C/C++)
- ReactJS (Web Dashboard)
- Firebase / MQTT (Cloud Communication)
- Visual Studio Code

---

## ⚙️ Working of the System
1. The MQ-3 sensor continuously monitors alcohol levels in the driver’s breath.
2. The ESP32 reads sensor data and compares it with a predefined threshold.
3. If alcohol exceeds the limit:
   - Vehicle ignition is blocked, or
   - Vehicle is slowed down safely if already in motion.
4. GPS location and alcohol data are sent to the cloud.
5. Authorities can monitor live data through a web dashboard.

---

## 🌐 Web Dashboard
The web dashboard is built using ReactJS and displays:
- Alcohol detection status
- Vehicle GPS location
- Alert history
- Real-time incident notifications

---

## 📁 Project Structure

SafeDrive-IoT/  
│  
├── documentation/  
│ └── SafeDrive_Report.pdf  
│  
├── arduino-code/  
│ └── safedrive.ino  
│  
├── web-dashboard/  
│ ├── App.js  
│ ├── App.css  
│  
├── diagrams/  
├── images/  
└── README.md  


---

## 📊 Results
- Accurate alcohol detection using MQ-3 sensor
- Safe vehicle control without abrupt stopping
- Real-time GPS tracking
- Successful cloud data transmission
- Effective remote monitoring by authorities

---

## 🔮 Future Enhancements
- Integration with vehicle ECU
- Face recognition for driver authentication
- Mobile application for alerts
- AI-based driver behavior analysis
- Enhanced data security and encryption

---

## 👨‍💻 Contributors
- Md Abdul Abed
- Ambati Sai Teja
- Gonewar Pavan Kumar
- Cheepelly Siddhartha

---

## 📜 Documentation
Detailed project documentation is available in the `documentation` folder.

---

## 📌 Note
This project was developed as part of a B.Tech Mini Project (2024–2025).
