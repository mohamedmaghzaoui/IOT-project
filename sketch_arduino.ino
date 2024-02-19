#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>
#include <Adafruit_NeoPixel.h>
#include <RemoteXY.h>
// RemoteXY connection settings
#define REMOTEXY_BLUETOOTH_NAME "chic"
#define PIN 17
#define NUMPIXELS 2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// RemoteXY configurate  
#pragma pack(push, 1)

uint8_t RemoteXY_CONF[] =   // 18 bytes

  { 255,3,0,0,0,11,0,16,31,1,6,0,20,38,20,20,2,26 };

 

// this structure defines all the variables and events of your control interface

struct {
    // input variables
  uint8_t rgb_1_r; // =0..255 Red color value

  uint8_t rgb_1_g; // =0..255 Green color value

  uint8_t rgb_1_b; // =0..255 Blue color value
    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0
} RemoteXY;

#pragma pack(pop)
/////////////////////////////////////////////

//           END RemoteXY include          //
/////////////////////////////////////////////
void setup()
{
  RemoteXY_Init ();
  pixels.begin();
}
void loop()
{
  pixels.begin();
  RemoteXY_Handler ();
  if (RemoteXY.rgb_1_r== 0){
    pixels.setPixelColor(0, pixels.Color(50, 0, 0));
    pixels.setPixelColor(1, pixels.Color(50, 0, 0));
   pixels.show();
 }
  if (RemoteXY.rgb_1_b== 0){
    pixels.setPixelColor(0, pixels.Color( 0,50, 0));
    pixels.setPixelColor(1, pixels.Color(0,50, 0));
   pixels.show();
 }

  else {
    pixels.setPixelColor(0, pixels.Color(0, 0, 50));
    pixels.setPixelColor(1, pixels.Color(0, 0, 50));
    pixels.show();
  }
}

 