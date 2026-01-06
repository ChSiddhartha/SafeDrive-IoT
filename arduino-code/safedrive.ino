#include <WiFi.h>
#include <PubSubClient.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#include <time.h>

// WiFi credentials
const char* ssid = "Pk123";
const char* password = "123456789";

// MQTT Broker
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp32/alcohol";

// GPS Serial Setup
HardwareSerial GPSserial(1);  // Use Serial1 (GPIO 16 RX, 17 TX)
TinyGPSPlus gps;

// MQ-3 Sensor
#define MQ3_PIN 34

// Motor A (Left)
const int IN1 = 14;
const int IN2 = 27;

// Motor B (Right)
const int IN3 = 25;
const int IN4 = 33;

// Buzzer
const int BUZZER_PIN = 4;

// Threshold
const int ALCOHOL_THRESHOLD = 2200;
bool isStopped = false;

// Fallback location if GPS fails
const float DEFAULT_LAT = 17.5203;  // Default latitude
const float DEFAULT_LON = 78.3674; // Default longitude

WiFiClient espClient;
PubSubClient client(espClient);

void moveForward();
void stopMotors();
void reconnectMQTT();
String getTimeStamp();
void readGPS();

void setup() {
  Serial.begin(115200);
  GPSserial.begin(9600, SERIAL_8N1, 16, 17);  // GPS baud, RX, TX

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  configTime(19800, 0, "pool.ntp.org"); // GMT+5:30 for IST
  delay(2000);

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  readGPS();

  if (isStopped) {
    stopMotors();
    digitalWrite(BUZZER_PIN, LOW);
    return;
  }

  int alcoholValue = analogRead(MQ3_PIN);
  float voltage = alcoholValue * (3.3 / 4095.0);
  String timeStamp = getTimeStamp();

  Serial.print("Alcohol Value: ");
  Serial.print(alcoholValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" | Time: ");
  Serial.println(timeStamp);

  if (alcoholValue > ALCOHOL_THRESHOLD) {
    Serial.println("⚠️ Alcohol Detected! STOP, Buzzer ON");
    stopMotors();
    digitalWrite(BUZZER_PIN, HIGH);
    isStopped = true;

    // Use GPS data or fallback to default if GPS is unavailable
    float lat = gps.location.isValid() ? gps.location.lat() : DEFAULT_LAT;
    float lon = gps.location.isValid() ? gps.location.lng() : DEFAULT_LON;

    String payload = "{";
    payload += "\"timestamp\":\"" + timeStamp + "\",";
    payload += "\"alcohol\":" + String(alcoholValue) + ",";
    payload += "\"voltage\":" + String(voltage, 2) + ",";
    payload += "\"latitude\":" + String(lat, 6) + ",";
    payload += "\"longitude\":" + String(lon, 6);
    payload += "}";

    Serial.println("📤 Sending MQTT payload:");
    Serial.println(payload);

    client.publish(mqtt_topic, payload.c_str());
  } else {
    Serial.println("✅ No Alcohol Detected. Moving Forward");
    digitalWrite(BUZZER_PIN, LOW);
    moveForward();
  }

  delay(1000);
}

void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32AlcoholClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

String getTimeStamp() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "NoTime";
  }
  char buffer[30];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(buffer);
}

void readGPS() {
  while (GPSserial.available() > 0) {
    gps.encode(GPSserial.read());
  }

  if (gps.location.isValid()) {
    Serial.print("📡 GPS: ");
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(", Lon: ");
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println("❌ GPS location not available");
  }
}