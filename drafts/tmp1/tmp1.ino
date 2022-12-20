#include "FastLED.h"

// const byte NUM_LEDS = 24; // Ring
const byte NUM_LEDS = 252;   // Ruban

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, 11>(leds, NUM_LEDS);
}

int hue = 0;

void loop() {

  FastLED.clear();
  for (int led = 0; led < NUM_LEDS; led++) {
    //uint8_t hue = map(led, 0, NUM_LEDS, 0, 254);
    //leds[led].setHue(hue);
    leds[led].setHue(hue);
    //leds[led].setHue(90);
  }
  FastLED.show();

  hue = (hue + 60) % 360;
  
  delay(2000);
}
