#include <ArduinoBLE.h>


const int ENA = 9;
const int IN1 = 10;
const int IN2 = 11;
const int ENB = 6;
const int IN3 = 7;
const int IN4 = 8;


const int trigFront = 2;
const int echoFront = 3;


bool autoMode = true;
bool trackingActive = false;
long distanceFront;
int rssiValue = 0;
float avgRSSI = -70; 


BLEService robotService("12345678-1234-1234-1234-123456789abc");
BLEStringCharacteristic statusChar("abcd", BLERead | BLENotify, 50);
BLECharacteristic controlChar("ef01", BLEWrite, 20);

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200); // communication with ESP32

  // Motors
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();

  // Ultrasonic
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);

  // BLE setup
  if (!BLE.begin()) {
    Serial.println("Starting Bluetooth failed!");
    while (1);
  }

  BLE.setLocalName("AutoBotNano");
  BLE.setAdvertisedService(robotService);
  robotService.addCharacteristic(statusChar);
  robotService.addCharacteristic(controlChar);
  BLE.addService(robotService);
  BLE.advertise();

  Serial.println("Bluetooth ready — Waiting for phone connection...");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.println("Phone Connected!");
    while (central.connected()) {
      // Handle incoming BLE commands
      if (controlChar.written()) {
        String command = getWrittenString();
        Serial.print("Command: "); Serial.println(command);

        if (command == "AUTO") {
          autoMode = true;
          trackingActive = true;
          Serial.println("Automatic mode ON");
        } 
        else if (command == "MANUAL") {
          autoMode = false;
          trackingActive = false;
          stopMotors();
          Serial.println("Manual mode");
        }
      }

      //ESP32
      if (Serial1.available()) {
        char cmd = Serial1.read();
        if (cmd == 'A') {
          autoMode = true;
          trackingActive = true;
          Serial.println("ESP32 → Automatic mode ON");
        } else if (cmd == 'M') {
          autoMode = false;
          trackingActive = false;
          stopMotors();
          Serial.println("ESP32 → Manual mode");
        }
      }

      
      if (autoMode && trackingActive) {
        runSmoothTracking(central);
      }

      delay(150);
    }
    Serial.println("Bluetooth Disconnected.");
    stopMotors();
  }
}


String getWrittenString() {
  int len = controlChar.valueLength();
  String s = "";
  for (int i = 0; i < len; i++) s += (char)controlChar.value()[i];
  return s;
}


void runSmoothTracking(BLEDevice central) {
  int newRSSI = central.rssi();
  avgRSSI = (0.8 * avgRSSI) + (0.2 * newRSSI); 

  Serial.print("Raw RSSI: ");
  Serial.print(newRSSI);
  Serial.print(" | Smoothed: ");
  Serial.println(avgRSSI);

  distanceFront = getDistance(trigFront, echoFront);

  String status = "RSSI: " + String(avgRSSI) + " | Dist: " + String(distanceFront);
  statusChar.writeValue(status);

  if (distanceFront < 20) {
    stopMotors();
    Serial.println("Obstacle ahead — stopping!");
    return;
  }

 
  if (avgRSSI < -73) {        // phone far away
    forward();
  } 
  else if (avgRSSI > -58) {   // too close
    backward();
  } 
  else {                      // safe following distance
    stopMotors();
  }
}


long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 20000);
  return duration * 0.034 / 2;
}


void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}
void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
