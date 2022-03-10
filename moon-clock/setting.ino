const int PIN_SETTING = 2;

const int MAX_COUNTER = floor(MOON_CYCLE_DURATION);

const int SETTING_TIMEOUT = 5 * 1000; // 10 seconds

int settingCounter = 0;

unsigned long lastSettingTime;

void setupSettings() {
  
  pinMode(PIN_SETTING, INPUT_PULLUP);
  printSetting();
  lastSettingTime = millis();
  
}

void loopSettings() {
  int button = digitalRead(PIN_SETTING);
  boolean buttonPressed = boolean(1-button);

  if((millis() - lastSettingTime) > SETTING_TIMEOUT) {
    
    for(int i=0; i<10; i++) {
      lightAll(HIGH);
      delay(50);
      lightAll(LOW);
      delay(50);
    }
    
    setClockStart(settingCounter);  
    mode = MODE_CLOCK;

    return;
  }
  
  if(buttonPressed) {

    settingCounter = (settingCounter + 1) % MAX_COUNTER;
    lastSettingTime = millis();
    printSetting();
    delay(200);
    
  }
}


void lightAll(int state) {
  for(int i=0; i<DISPLAY_PRECISION; i++) {
    digitalWrite(PINS_START + i, state);
  }
}

void printSetting() {

  debug("Day: "); debugln(String(settingCounter));
    
  if(settingCounter == 0) {
    lightAll(HIGH);
  } else {
    lightAll(LOW);
    int off = settingCounter % (DISPLAY_PRECISION + 1);
    if(off > 0) {
      digitalWrite(PINS_START + off - 1, HIGH);
    }
  }
  
}
