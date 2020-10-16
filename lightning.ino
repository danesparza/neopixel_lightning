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
  /*
  Serial.begin(9600);
  Serial.print(NUMBER_OF_COLORS);
  */
  
  strip.begin();
  strip.setBrightness(ambient_brightness);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  //  Set our initial ambient light:
  set_ambient_lighting(4, 0, 26);
  
  /*
  //  LS1
  lightening_pulse(100, false);
  delay(100); //  Gap length
  
  lightening_pulse(10, false);  
  delay(10); //  Gap length

  lightening_pulse(10, false);
  delay(10); //  Gap length

  lightening_pulse(20, false);
  delay(50); //  Gap length

  lightening_pulse(10, false);
  delay(10); //  Gap length
  //  LS1 END
  */

  //  Pick a random lightning 'roll' time:
  int randRoll = random(500, 3500);
  lightening_rando_pulse(randRoll);

  //  Switch back to ambient light:
  set_ambient_lighting(4, 0, 26);
  
  //  Adjust the delay here, if you'd like.  Right now, it randomizes the 
  //  color switch delay to give a sense of realism
  delay(random(5000,20000));
}

//  'Pulse' lightning for the specified amount of time (in milliseconds) 
void lightening_pulse(int pulselength, bool randomizebrightness)
{
  int currentBrightness = lightning_brightness;
  
  if(randomizebrightness) 
  {
    currentBrightness = random(ambient_brightness, lightning_brightness);
  }
  
  strip.setBrightness(currentBrightness);
  
  //  Show lightening pulse:
  for(int i=0; i<strip.numPixels(); i++) {    
    strip.setPixelColor(i,255,255,255);
  }
  strip.show();
  delay(pulselength); //  Show for pulse length

  //  Turn everything back off
  for(int i=0; i<strip.numPixels(); i++) {    
    strip.setPixelColor(i,0,0,0);
  }
  strip.show();
}

//  Simulate a random strike for (around) the specified 
//  number of milliseconds.  This will essentially give some randomized
//  'lightning' pulses for a certain amount of time.
void lightening_rando_pulse(int totaltime)
{
  //  Keep track of light pulse time and gap time
  int timeSpent = 0;
  
  //  For the amount of time specified ...
  while (timeSpent < totaltime) {
    //  Pick a random pulse time
    int randPulseTime = random(10, 200);
    
    //  Pick a random delay time
    int randDelayTime = random(5, 100);

    //  Add both the pulse and delay times to the time spent
    timeSpent = timeSpent + randPulseTime + randDelayTime;

    //  Pulse & Delay
    lightening_pulse(randPulseTime, true);  
    delay(randDelayTime); //  Gap length
  }
  
}

//  Set the ambient light to the RGB values specified
void set_ambient_lighting(int r, int g, int b)
{
  strip.setBrightness(ambient_brightness);
  
  for(int i=0; i<strip.numPixels(); i++) {    
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();  
}

