#include "FastLED.h"

const byte NUM_LEDS = 24; // Ring
//const byte NUM_LEDS = 100;   // Ruban

CRGB leds[NUM_LEDS];

void setup_light() { 
  FastLED.addLeds<NEOPIXEL, 11>(leds, NUM_LEDS);
  FastLED.clear();
}


void light_rotate(long mod_time) {
  unsigned long t = millis();
  
  float freq = mod_time / 200.;
  //Serial.print(mod_time); Serial.print("\t"); Serial.println(freq);


 //freq= 0.5;
  for(int led = 0; led < NUM_LEDS; led++) { 
    byte angle = map(led, 0, NUM_LEDS, 0, 255);
    byte hue = sin8(t * freq + angle);
    leds[led].setHSV(hue, 255, 120);
  }
  FastLED.show();
}
