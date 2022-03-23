void setupLight() {
  debugln("Setup light");
  
  for(byte i=0; i<DISPLAY_PRECISION; i++) {
    pinMode(PINS_START + i, OUTPUT);
  }

  lightAll(LOW);
}

void lightOne(byte index, byte state) {
  digitalWrite(PINS_START + index, state);
}

void lightAll(byte state) {
  for(int i=0; i<DISPLAY_PRECISION; i++) {
    lightOne(i, state);
  }
}

void strobo() {
  for(byte i=0; i<10; i++) {
    lightAll(HIGH);
    delay(50);
    lightAll(LOW);
    delay(50);
  }
}
