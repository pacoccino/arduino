int mode;

void setup() {

  // Stop built in light
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  mode = MODE_SETTING;
  setupDebug();
  setupLight();
  setupClock();
  setupSetting();
}

void loop() {
  switch(mode) {
    case MODE_SETTING: {
      loopSetting();
      break;
    }
    case MODE_CLOCK: {
      loopClock();
      break;
    }
  }
}
