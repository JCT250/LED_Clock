#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int c_r = 255;
int c_g = 255;
int c_b = 255;
int face_intent = 8; // change this value to alter the brightness of the face. Whatever value is used must return a whole number when 256 is divided by it

int hours = 1; 
int mins = 0;
int secs = 0;
int hours_old = 0;
int mins_old = 0;
int secs_old = 0;

int update_time = 0;
int display_off = 0;

RTC_DS1307 RTC;

void setup() 
{
  Serial.begin(57600);
  strip.begin();
  Wire.begin();
  RTC.begin();
  strip.show(); // Initialize all pixels to 'off'

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  rainbowCycle(20); // a little bit of eye candy on startup
}

void loop() 
{
  get_time();

  if(update_time == 1)
  {
    Serial.print(hours);
    Serial.print(':');
    Serial.print(mins);
    Serial.print(':');
    Serial.print(secs);
    Serial.println();
    if(hours > 7 && hours <= 17 && display_off == 2)display_off = 0;
    if(hours > 17 && display_off == 0) display_off = 1;
    if(display_off == 1){
      for(int m=0; m<strip.numPixels(); m++) {
        strip.setPixelColor(m,0,0,0);
        strip.show();
        delay(20);
      }
      display_off = 2;
    }
    if(display_off == 0){
      set_face();
      set_hours();
      set_minutes();
      set_seconds();
      strip.show();
    }
    update_time = 0;
    hours_old = hours;
    mins_old = mins;
    secs_old = secs;
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*1; j++) { // change value after 256* to adjust number of sweeps
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void set_face()
{
  for(int m=0; m<60; m++) strip.setPixelColor(m,0,0,0);
  for(int i=0; i<60; i=i+5) {
    strip.setPixelColor(i,(c_r+1)/face_intent,(c_g+1)/face_intent,(c_b+1)/face_intent); 
  }
}

void set_hours()
{
  switch (hours)
  {
  case 1:
    strip.setPixelColor(4,0,c_g,0);
    strip.setPixelColor(6,0,c_g,0);
    break;
  case 2:
    strip.setPixelColor(9,0,c_g,0);
    strip.setPixelColor(11,0,c_g,0);
    break;
  case 3:
    strip.setPixelColor(14,0,c_g,0);
    strip.setPixelColor(16,0,c_g,0);
    break;
  case 4:
    strip.setPixelColor(19,0,c_g,0);
    strip.setPixelColor(21,0,c_g,0);
    break;
  case 5:
    strip.setPixelColor(24,0,c_g,0);
    strip.setPixelColor(26,0,c_g,0);
    break;
  case 6:
    strip.setPixelColor(29,0,c_g,0);
    strip.setPixelColor(31,0,c_g,0);
    break;
  case 7:
    strip.setPixelColor(34,0,c_g,0);
    strip.setPixelColor(36,0,c_g,0);
    break;
  case 8:
    strip.setPixelColor(39,0,c_g,0);
    strip.setPixelColor(41,0,c_g,0);
    break;
  case 9:
    strip.setPixelColor(44,0,c_g,0);
    strip.setPixelColor(46,0,c_g,0);
    break;
  case 10:
    strip.setPixelColor(49,0,c_g,0);
    strip.setPixelColor(51,0,c_g,0);
    break;
  case 11:
    strip.setPixelColor(54,0,c_g,0);
    strip.setPixelColor(56,0,c_g,0);
    break;
  case 12:
    strip.setPixelColor(59,0,c_g,0);
    strip.setPixelColor(1,0,c_g,0);
    break;
  case 13:
    strip.setPixelColor(4,0,c_g,0);
    strip.setPixelColor(6,0,c_g,0);
    break;
  case 14:
    strip.setPixelColor(9,0,c_g,0);
    strip.setPixelColor(11,0,c_g,0);
    break;
  case 15:
    strip.setPixelColor(14,0,c_g,0);
    strip.setPixelColor(16,0,c_g,0);
    break;
  case 16:
    strip.setPixelColor(19,0,c_g,0);
    strip.setPixelColor(21,0,c_g,0);
    break;
  case 17:
    strip.setPixelColor(24,0,c_g,0);
    strip.setPixelColor(26,0,c_g,0);
    break;
  case 18:
    strip.setPixelColor(29,0,c_g,0);
    strip.setPixelColor(31,0,c_g,0);
    break;
  case 19:
    strip.setPixelColor(34,0,c_g,0);
    strip.setPixelColor(36,0,c_g,0);
    break;
  case 20:
    strip.setPixelColor(39,0,c_g,0);
    strip.setPixelColor(41,0,c_g,0);
    break;
  case 21:
    strip.setPixelColor(44,0,c_g,0);
    strip.setPixelColor(46,0,c_g,0);
    break;
  case 22:
    strip.setPixelColor(49,0,c_g,0);
    strip.setPixelColor(51,0,c_g,0);
    break;
  case 23:
    strip.setPixelColor(54,0,c_g,0);
    strip.setPixelColor(56,0,c_g,0);
    break;
  case 0:
    strip.setPixelColor(59,0,c_g,0);
    strip.setPixelColor(1,0,c_g,0);
    break;
  } 
}

void set_minutes()
{
  strip.setPixelColor(mins,0,0,c_b);
}

void set_seconds()
{
  strip.setPixelColor(secs,c_r,0,0);
}

void get_time()
{
  DateTime now = RTC.now();
  hours =  now.hour();
  mins = now.minute();
  secs = now.second();
  if(hours != hours_old) update_time = 1;
  if(mins != mins_old) update_time = 1;
  if(secs != secs_old) update_time = 1;

}














