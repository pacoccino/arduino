const int PIN_SETTING = 2;

const int MAX_COUNTER = floor(MOON_CYCLE_DURATION);

const int SETTING_TIMEOUT = 5 * 1000; // 5 seconds

int settingCounter = 0;
bool settingPristine = true;

unsigned long lastSettingTime;

void setupSetting() {
  debugln("Setup setting");
  
  pinMode(PIN_SETTING, INPUT_PULLUP);
  lastSettingTime = millis();
  strobo();
  printSetting();
}

void loopSetting() {
  int button = digitalRead(PIN_SETTING);
  boolean buttonPressed = boolean(1-button);

  if(!settingPristine && (millis() - lastSettingTime) > SETTING_TIMEOUT) {
    debugln("timeout settings");
    
    strobo();
    
    setClockStart(settingCounter);  
    mode = MODE_CLOCK;

    return;
  }
  
  if(buttonPressed) {
    debugln("setup: button pressed");
    
    settingPristine = false;
    settingCounter = (settingCounter + 1) % MAX_COUNTER;
    lastSettingTime = millis();
    printSetting();
    delay(200);
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
      lightOne(off - 1, HIGH);
    }
  }
  
}
