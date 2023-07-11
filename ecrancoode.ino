//necessaty libraries
#include <Wire.h> //for i2c
#include <string.h>
#include <SoftwareWire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SEALEVELPRESSURE_HPA (1013.25)
#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64);
int sensorPin = A0; // moisture sensor  connected to A0
void setup() {
   Wire.begin(0x3C);
  Serial.begin(9600); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
}
void loop() {
 int sensorValue = analogRead(sensorPin); // read the sensor value
 Serial.print(sensorValue);
 int moisturePercent = map(sensorValue, 654 , 325, 0, 100); // map the sensor value to a percentage value
  display.clearDisplay();
  display.setTextSize(2); // text size
  display.setTextColor(WHITE); // text color
  display.setCursor(0,0); // position
  //display soil value in %
  display.print("Sol:  ");
  display.print(moisturePercent); 
  display.print("%"); 
  display.display(); 
  delay(2000);
}