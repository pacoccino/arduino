
void setupLight() {
  debugln("Setup light");
  
  for(int i=0; i<DISPLAY_PRECISION; i++) {
    pinMode(PINS_START + i, OUTPUT);
  }

  lightAll(LOW);
}

void lightOne(int index, int state) {
  digitalWrite(PINS_START + index, state);
}

void lightAll(int state) {
  for(int i=0; i<DISPLAY_PRECISION; i++) {
    lightOne(i, state);
  }
}

void strobo() {
  for(int i=0; i<10; i++) {
    lightAll(HIGH);
    delay(50);
    lightAll(LOW);
    delay(50);
  }
}
