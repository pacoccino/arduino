#include "FastLED.h"

// const byte NUM_LEDS = 24; // Ring
const byte NUM_LEDS = 252;   // Ruban

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, 11>(leds, NUM_LEDS);

  FastLED.clear();
}

const int len = 8000;

void loop() {
  unsigned long now = millis();

  unsigned int reap = now % len;
  unsigned int offset = map(reap, 0, len, 0, 255);
  light_1(offset);
  //light_2();
}

void light_1(unsigned int offset) {
  for (int led = 0; led < NUM_LEDS; led++) {
    uint8_t hue = (map(led, 0, NUM_LEDS, 0, 254) + offset) % 255;
    leds[led].setHue(hue);
  }
  FastLED.show();
}

void light_2() {
  for (int led = 0; led < NUM_LEDS; led++) {
    uint8_t hue = random(0, 255);
    leds[led].setHue(hue);
  }
  FastLED.show();
  delay(200);
}
