#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 180

//  Brightness
//  (this can affect both color levels and power consumption)
//  (max = 255)
int lightning_brightness = 100;
int ambient_brightness = 10;

struct RGB {
  byte r;
  byte g;
  byte b;
};

//  The flame color array (the first is the default):
RGB flameColors[] = {
  { 226, 121, 35},  // Orange flame
  { 158, 8, 148},   // Purple flame 
  { 74, 150, 12},   // Green flame
  { 226, 15, 30}    // Red flame
  };

//  Number of flame colors
int NUMBER_OF_COLORS = sizeof(flameColors) / sizeof(RGB);

//  Tracks the current color
int currentColorIndex = 0;

//  The button pin
const int buttonPin = 2;

//  Variable for reading the pushbutton status
int buttonState = 0;         

//  Tracking if it's ok to shift colors or not
bool okToChangeColors = true;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first and disconnect GND last.
// For the ultimate NeoPixel guide, check out:
// https://learn.adafruit.com/adafruit-neopixel-uberguide/overview

void setup() {
  Serial.begin(9600);
  Serial.print(NUMBER_OF_COLORS);
  
  strip.begin();
  strip.setBrightness(ambient_brightness);
  strip.show(); // Initialize all pixels to 'off'

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  set_ambient_lighting(4, 0, 26);
  delay(5000);
  
  lightening_pulse(100);
  delay(100); //  Gap length
  
  lightening_pulse(10);  
  delay(10); //  Gap length

  lightening_pulse(10);
  delay(10); //  Gap length

  lightening_pulse(20);
  delay(50); //  Gap length

  lightening_pulse(10);
  delay(10); //  Gap length

  set_ambient_lighting(4, 0, 26);
  
  //  Adjust the delay here, if you'd like.  Right now, it randomizes the 
  //  color switch delay to give a sense of realism
  delay(random(1000,7000));
}

void lightening_pulse(int pulselegth)
{
  strip.setBrightness(lightning_brightness);
  
  //  Show lightening pulse:
  for(int i=0; i<strip.numPixels(); i++) {    
    strip.setPixelColor(i,255,255,255);
  }
  strip.show();
  delay(pulselegth); //  Show for pulse length

  //  Turn everything back off
  for(int i=0; i<strip.numPixels(); i++) {    
    strip.setPixelColor(i,0,0,0);
  }
  strip.show();
}

void set_ambient_lighting(int r, int g, int b)
{
  strip.setBrightness(ambient_brightness);
  
  for(int i=0; i<strip.numPixels(); i++) {    
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();  
}

