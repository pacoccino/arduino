const float MOON_CYCLE_DURATION = 29.530588; // days

const unsigned long DAYS_TO_MS = 24L * 60L * 60L * 1000L;
// const unsigned long DAYS_TO_MS = 500L; // For debug

const byte MOON_PHASES = 8;

const float PHASE_DURATION = MOON_CYCLE_DURATION / MOON_PHASES;

// In North hemisphere
const int PHASES[MOON_PHASES][DISPLAY_PRECISION] = {
  {LOW,LOW,LOW,LOW},        // New
  {LOW,LOW,LOW,HIGH},       // Waxing Crescent
  {LOW,LOW,HIGH,HIGH},      // First Quarter 
  {LOW,HIGH,HIGH,HIGH},     // Waxing Gibbous
  {HIGH,HIGH,HIGH,HIGH},    // Full
  {HIGH,HIGH,HIGH,LOW},     // Waning Gibbous
  {HIGH,HIGH,LOW,LOW},      // Third Quarter
  {HIGH,LOW,LOW,LOW}        // Waning Crescent
};

void setupClock() {
  debugln("Setup clock");
}

byte currentPhase = 0;
unsigned long nextPhaseTime;
// word nextPhaseTime_w;
boolean overflowing = false;

void initClock(int startDay) {  
  debugln("Init clock");
  
  unsigned long now = millis();
  // word now_w = word(now);
  
  float startOffset = fmod(startDay, PHASE_DURATION);
  currentPhase = floor(startDay / PHASE_DURATION);
  nextPhaseTime = now + (PHASE_DURATION - startOffset) * DAYS_TO_MS;
  //nextPhaseTime_w = now_w + (PHASE_DURATION - startOffset) * DAYS_TO_MS;
  
 
  debug("Phase duration: "); debugln(String(PHASE_DURATION));
  debug("Start offset: "); debugln(String(startOffset));
  
  printPhase();
}

void printPhase() {
  debug("-- Phase: "); debugln(String(currentPhase));
  
  const int *phaseArray = PHASES[currentPhase];
  
  for(int i=0; i<DISPLAY_PRECISION; i++) {
    lightOne(i, phaseArray[i]);
  }
}

unsigned long lastTime = 0;
// word lastTime_w = 0;

void loopClock() {
  unsigned long now = millis();
  // word now_w = word(now);

  /*
  debug("now\t"); debugln(String(now));
  debug("next\t"); debugln(String(nextPhaseTime));
  debug("overflowing\t"); debugln(String(overflowing));
  */
  
  if(overflowing && lastTime > now) {
    overflowing = false;
    debugln("overflow disabled");
  }
  
  lastTime = now;
  // lastTime_w = now_w;
  
  if(!overflowing && now >= nextPhaseTime) {
    
    currentPhase = (currentPhase + 1) % MOON_PHASES;
    nextPhaseTime = nextPhaseTime + PHASE_DURATION * DAYS_TO_MS;
    // nextPhaseTime_w = nextPhaseTime_w + PHASE_DURATION * DAYS_TO_MS;
    overflowing = nextPhaseTime < now;
    if(overflowing) { 
      debugln("overflow caught");
    }
    
    printPhase();
    
  } else {
    delay(300);
  }
}
