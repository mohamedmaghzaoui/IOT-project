#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

Adafruit_BME280 bme;  // Create an instance of the BME280 sensor
#define SDA_PIN 33
#define SCL_PIN 32
const char* ssid = "mohamed's Galaxy A14";
const char* password = "testMohamedEsp32";

void setup() {
  // Set up Serial for debugging output
  Serial.begin(9600);

  Wire.begin(SDA_PIN, SCL_PIN);
  if (!bme.begin(0x77)) {  // Adjust the address if necessary (0x76 or 0x77)
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
    // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print your ESP32 IP address
  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Add your sensor reading and JSON data creation here

  float altitude = bme.readAltitude(1013.25);
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0;

  // Print sensor data
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" meters");

  // JSON data
  DynamicJsonDocument doc(200);
  doc["temperature"] = temperature;
  doc["pressure"] = pressure;
  doc["humidity"] = humidity;
  doc["altitude"] = altitude;

  String jsonString;
  serializeJson(doc, jsonString);
  Serial.println("Sensor Data:");
  Serial.println(jsonString);
  HTTPClient http;

  // Your server URL
  const char* serverUrl = "http://192.168.50.92:3000/";

  // Make HTTP POST request
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonString);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println("Response: " + response);
  } else {
    Serial.print("Error in HTTP request: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  delay(10000);
}
