const int MODE_SETTING = 0;
const int MODE_CLOCK = 1;

int mode = MODE_SETTING;

void setup() {
 
  enableDebug();

  // Stop built in light
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  setupClock();
  setupSettings();
  
}

void loop() {

  if(mode == MODE_SETTING) {
    loopSettings();
  } else if (mode == MODE_CLOCK) {
    loopClock();
  }
  
}
