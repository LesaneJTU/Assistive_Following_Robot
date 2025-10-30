# Assistive_Following_Robot

#  AutoNanoBot

## **Table of Contents**
- [Repository Content](#repository-content)  
- [About AutoNanoBot Documentation](#about-autonanobot-documentation)  
- [Acknowledgment](#acknowledgment)  
- [Introduction](#introduction)  
- [Objective](#objective)  
- [Functionalities](#functionalities)  
- [Hardware Requirements](#hardware-requirements)  
- [Software Requirements](#software-requirements)  
- [Project Description](#project-description)  
- [Applications](#applications)  
- [Performance Flow](#performance-flow)  
- [How to Use / Setup Instructions](#how-to-use--setup-instructions)
- [Circuit Diagram](#Circuit-Diagram)
- [Performance Flow](#Performance-Flow)
- [Image Of Prototype](#Image-Of-Prototype)
- [Video Of Prototype Build](#Image-Of-Prototype-Build)
- [Conclusion](#conclusion)  

---
## **Repository Content**

| **File / Folder** | **Description** |
|-------------------|-----------------|
| **IMG/** | Folder containing images of the robot and components. |
| **src/** | Source code for Arduino Nano BLE 33 Sense and ESP32. |
| **AutoNanoBot UserManual** | User Manual |
| **BillOfMaterial.pdf** | Complete Bill of Materials listing all components used. |
| **Circuit-Diagram.png** | Circuit diagram showing wiring and connections of the robot. |
| **PerformanceFlow.jpg** | Image illustrating the performance flow of the robot. |
| **README.md** | Documentation and instructions for the AutoNanoBot project. |

---
## **About AutoNanoBot Documentation**
AutoNanoBot is a given project focused on building an assistive following robot designed to carry items and automatically follow its user. The robot combines both **manual** and **automatic** control using **Arduino Nano 33 BLE Sense** and **ESP32**, enabling it to detect and avoid obstacles while following a person through Bluetooth or Wi-Fi. This project demonstrates the integration of electronics, sensors, motor control, and communication systems in a real-world assistive robotics application.

---

## **Acknowledgment**
This project was developed as part of a given assignment. Special thanks to instructors, mentors, and peers for their guidance and feedback throughout the building and testing process.

---

## **Introduction**
AutoNanoBot is an assistive robot designed to follow a person and carry items automatically. It uses sensors and programmed control to detect movement, maintain distance, and avoid obstacles. The project serves as a practical exercise in robotics, electronics, and programming, applying real-world concepts through hands-on learning.

---

## **Objective**
The objective of AutoNanoBot is to reduce physical strain by helping users carry heavy or multiple items over short distances. It aims to assist the elderly, people with mobility challenges, or anyone needing help transporting groceries, tools, or equipment. The goals are to design and build a functional robot that can **follow**, **avoid obstacles**, and **carry items** while providing hands-on learning in **electronics**, **sensors**, **motors**, and **programming**.

---

## **Functionalities**
-  **Automatic Following Mode:** Follows a smartphone using Bluetooth LE signals.  
-  **Obstacle Avoidance:** Uses ultrasonic sensors to detect objects within 70 cm.  
-  **Dual Operation:** Switch between manual (Wi-Fi via ESP32) and automatic (Bluetooth via Nano).  
-  **Two-Board Communication:** Data synchronization via UART between ESP32 and Arduino Nano BLE 33 Sense.  
-  **Safety Feature:** Robot stops automatically if the Bluetooth connection is lost or an obstacle is too close.  

---

## **Hardware Requirements**

| **Component Name** | **Purpose in Project** | **Quantity** |
|--------------------|------------------------|--------------|
| **ESP32** | Main microcontroller for manual Wi-Fi control and communication. | 1 |
| **Arduino Nano BLE 33 Sense** | Handles automatic mode, Bluetooth tracking, and obstacle detection. | 1 |
| **L298N Motor Driver** | Controls motor speed and direction. | 1 |
| **12V DC Geared Motors** | Drive the robot and provide movement control. | 2 |
| **Li-ion 18650 Battery Cells** | Power source for motors and electronics. | 4 |
| **18650 Battery Holder** | Safely holds and connects batteries. | 1 |
| **5V DC-DC Step-Down Regulator** | Converts battery voltage to 5V for components. | 1 |
| **On/Off Rocker Switch** | Turns the system on and off safely. | 1 |
| **USB Cable** | Used for programming and debugging. | 1 |
| **Breadboard** | For temporary circuit prototyping. | 1 |
| **Capacitors (0.1µF, 220µF, 10µF)** | Stabilize power and reduce electrical noise. | 4 |
| **Ultrasonic Sensors** | Measure distance and detect obstacles. | 2 |
| **Caster Wheel** | Balances the chassis with two drive wheels. | 1 |
| **T-Slot Aluminium Extrusion** | Structural frame for mounting components. | 3 |

### **Additional Materials**
- **LEDs:** Status indicators for power, signals, or debugging.  
- **Connecting Wires:** Electrical connections between all components.  
- **3D Printing:** Custom brackets and support parts for stability.  
- **Laser-Cut Frames:** Provide sturdy structure and chassis design.  
- **Nuts, Bolts, Heat Inserts, Zip Ties:** Assembly and reinforcement materials.  

---

## **Software Requirements**

| **Software / Library** | **Purpose** |
|--------------------------|-------------|
| **Arduino IDE** | For writing, uploading, and debugging code. |
| **ESP32 Board Package** | Adds support for ESP32 programming. |
| **ArduinoBLE Library** | Enables Bluetooth Low Energy communication. |
| **WiFi Library (ESP32)** | Enables Wi-Fi connectivity for manual control. |
| **BluetoothSerial Library (ESP32)** | For simple Bluetooth communication and debugging. |
| **Wire Library** | Enables I²C communication with sensors. |
| **Onshape** | For CAD designing of the model |
| **CorelDRAW** | Laser-Cut Application |

---

## **Project Description**
**Step 1:** Defined robot requirements — automatic following, obstacle avoidance, and dual communication via Wi-Fi and Bluetooth.  
**Step 2:** Designed and tested the chassis using CAD for strength and stability.  
**Step 3:** Mounted the **L298N motor driver** for control of DC motors.  
**Step 4:** Completed circuit wiring for motors, sensors, and controllers.  
**Step 5:** Mounted the **Arduino Nano BLE 33 Sense** and motor driver securely.  
**Step 6:** Installed ultrasonic sensors for obstacle detection.  
**Step 7:** Configured **Wi-Fi** and **Bluetooth LE** for connectivity.  
**Step 8:** Integrated the **ESP32** for manual control and data collection.  
**Step 9:** Established **UART communication** for synchronized control and reliable switching between modes.

---

## **Applications**
- Assists people with **mobility challenges** by carrying items.  
- Used in **home automation** or **delivery robots**.  
- Can serve as a **personal assistant robot** for daily tasks.  
- Educational tool for **robotics and programming learning**.  
- Prototype for **warehouse or factory following carts**.

---

## **Performance Flow**
1. System powers on and initializes sensors and microcontrollers.  
2. Bluetooth connects to the mobile device for automatic following mode.  
3. Ultrasonic sensors measure distances and detect obstacles.  
4. Motors adjust speed and direction based on sensor data.  
5. ESP32 enables manual override through Wi-Fi if needed.  
6. Robot continues to follow the user while avoiding obstacles safely.  

---

## **How to Use / Setup Instructions**

### **Hardware Setup**
1. Assemble the chassis with frame, motors, caster wheel, and brackets.  
2. Mount the **Arduino Nano BLE 33 Sense** and **ESP32**, then connect the **L298N motor driver** to motors.  
3. Install **ultrasonic sensors** and **LED indicators**.  
4. Insert **Li-ion batteries** and connect through the **5V step-down regulator**.  
5. Add the **on/off rocker switch** for safe power control.  
6. Secure wiring and use **capacitors** for noise reduction and stability.  

### **Software Setup**
1. Install [Arduino IDE](https://www.arduino.cc/en/software) and add **ESP32 board support**.  
2. Install the required libraries: ArduinoBLE, WiFi (ESP32), BluetoothSerial (ESP32), Adafruit_Sensor.  
3. Connect microcontrollers via USB and upload their respective sketches.  
4. Set up the MIT App Inventor mobile app and connect via **Bluetooth LE** for automatic following or **Wi-Fi** for manual control.  

### **Quick Start**
1. Power on the robot with the **rocker switch**.  
2. Connect your phone via Bluetooth for automatic following.  
3. Optionally enable Wi-Fi for manual control.  
4. Place items on the robot platform.  
5. Walk and allow the robot to follow safely, observing obstacle avoidance.

## **Circuit Diagram**
<img width="610" height="672" alt="Circuit-Diagram" src="https://github.com/user-attachments/assets/aa720eaf-116b-46a1-befd-5499d46022b0" />

## **Performance Flow**
![PerformanceFlow](https://github.com/user-attachments/assets/ea4e71d6-1fa5-493a-8ae4-74ea6979159b)

## **Image Of Prototype**
<img width="723" height="388" alt="Screenshot 2025-10-17 170346" src="https://github.com/user-attachments/assets/9b4a8d04-fe4d-46b3-8d8a-aa07c3643177" />

## **Video Of Prototype Build**
https://youtube.com/shorts/LTWfOVC-fHk?si=KMNfo4rb8dLnHhu_ 
---

## **Conclusion**
AutoNanoBot demonstrates how multiple microcontrollers, communication protocols, and sensors can be combined to create a functional assistive robot. The project provides practical experience in electronics, programming, and robotics while laying the foundation for future enhancements such as camera tracking, or advanced navigation.
