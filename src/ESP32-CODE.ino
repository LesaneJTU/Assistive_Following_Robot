#include <WiFi.h>

// Wi-Fi credentials
const char* ssid = "E********";
const char* password = "a********";

// Web server
WiFiServer server(80);

// Serial pins to Nano
#define RXD2 16
#define TXD2 17

// LEDs
#define LED_F 27   // Forward
#define LED_B 26   // Backward
#define LED_S 32   // Stop
#define LED_MODE 14 // Manual/Auto
#define LED_WIFI 33
#define LED_POWER 25

// Forward movement variables
bool forwardActive = false;
unsigned long forwardStartTime = 0;
const unsigned long forwardDuration = 10000; // 10 seconds max

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Initialize LEDs
  pinMode(LED_F, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_S, OUTPUT);
  pinMode(LED_MODE, OUTPUT);
  pinMode(LED_WIFI, OUTPUT);
  pinMode(LED_POWER, OUTPUT);

  // Power LED ON
  digitalWrite(LED_POWER, HIGH);

  // Connect Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");
  digitalWrite(LED_WIFI, HIGH);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  
  if (client) {
    String request = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;

        if (c == '\n') {
          // Turn off movement LEDs before updating
          digitalWrite(LED_F, LOW);
          digitalWrite(LED_B, LOW);
          digitalWrite(LED_S, LOW);
          digitalWrite(LED_MODE, LOW);

          
          if (request.indexOf("GET /F") >= 0) {
            Serial.println("Forward button pressed");
            forwardActive = true;
            forwardStartTime = millis();
            digitalWrite(LED_F, HIGH);
          } 
          else if (request.indexOf("GET /B") >= 0) {
            Serial.println("Backward");
            Serial2.println("B");
            digitalWrite(LED_B, HIGH);
            forwardActive = false; 
          } 
          else if (request.indexOf("GET /S") >= 0) {
            Serial.println("Stop");
            Serial2.println("S");
            digitalWrite(LED_S, HIGH);
            forwardActive = false;
          } 
          else if (request.indexOf("GET /M") >= 0) {
            Serial.println("Manual");
            Serial2.println("M");
            digitalWrite(LED_MODE, HIGH);
          } 
          else if (request.indexOf("GET /A") >= 0) {
            Serial.println("Automatic");
            Serial2.println("A");
            digitalWrite(LED_MODE, HIGH);
          }

          
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
          client.println("Command received");
          break;
        }
      }
    }
    delay(1);
    client.stop();
  }

 
  if (forwardActive) {
    // Send forward command to Nano
    Serial2.println("F");

    // Check if Nano sent STOP due to sensors
    if (Serial2.available()) {
      String sensorMsg = Serial2.readString();
      sensorMsg.trim();
      if (sensorMsg == "STOP") {
        Serial.println("Obstacle detected! Stopping early.");
        forwardActive = false;
        digitalWrite(LED_F, LOW);
        Serial2.println("S");
      }
    }

    // Stop if max duration exceeded
    if (millis() - forwardStartTime >= forwardDuration) {
      Serial.println("Max forward duration reached");
      forwardActive = false;
      digitalWrite(LED_F, LOW);
      Serial2.println("S");
    }
  }
}
