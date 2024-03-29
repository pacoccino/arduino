const word MAX_COUNTER = floor(MOON_CYCLE_DURATION);

const word SETTING_TIMEOUT = 5 * 1000; // 5 seconds

word settingCounter = 0;
bool settingPristine = true;

unsigned long lastSettingTime;

void setupSetting() {
  debugln("Setup settings");
  
  pinMode(PIN_SETTING, INPUT_PULLUP);
  lastSettingTime = millis();
  strobo();
  lightAll(HIGH);
}

void loopSetting() {
  if(!settingPristine && (millis() - lastSettingTime) > SETTING_TIMEOUT) {
    debugln("Settings: timeout");
    
    strobo();
    
    initClock(settingCounter);  
    mode = MODE_CLOCK;
    debugln("Clock mode");
    
    return;
  }
  
  int button = digitalRead(PIN_SETTING);
  boolean buttonPressed = boolean(1-button);
  if(buttonPressed) {
    debugln("Settings: button pressed");
    lastSettingTime = millis();

    if(settingPristine) { // void first press to be able to set day 0
      settingPristine = false;
    } else {
      settingCounter = (settingCounter + 1) % MAX_COUNTER;
    }
   
    printSetting();
    delay(200);
  }
}

void printSetting() {

  debug("Day: "); debugln(String(settingCounter));
    
  if(settingCounter == 0) {
    lightOne(0, HIGH);
    lightOne(1, LOW);
    lightOne(2, LOW);
    lightOne(3, HIGH);
    
  } else {
    lightAll(LOW);
    int off = settingCounter % (DISPLAY_PRECISION + 1);
    if(off > 0) {
      lightOne(off - 1, HIGH);
    }
  }
  
}
