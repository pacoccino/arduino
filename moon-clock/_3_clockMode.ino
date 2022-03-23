const float MOON_CYCLE_DURATION = 29.530588; // days

//const unsigned long DAYS_TO_MS = 24L * 60L * 60L * 1000L;
const unsigned long DAYS_TO_MS = 1000L; // For debug

const int MOON_PHASES = 8;

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

int currentPhase = 0;
unsigned long nextPhaseTime;
boolean overflowing = false;

void initClock(int startDay) {  
  unsigned long now = millis();
  
  float startOffset = fmod(startDay, PHASE_DURATION);
  currentPhase = floor(startDay / PHASE_DURATION);
  nextPhaseTime = now + (PHASE_DURATION - startOffset) * DAYS_TO_MS;
  
  debug("Phase duration: "); debugln(String(PHASE_DURATION));
  debug("Start offset: "); debugln(String(startOffset));
  
  printPhase(currentPhase);
}

void printPhase(int phase) {
  debug("Phase: "); debugln(String(phase));
  
  const int *phaseArray = PHASES[phase];
  
  for(int i=0; i<DISPLAY_PRECISION; i++) {
    lightOne(i, phaseArray[i]);
  }
}

unsigned long lastTime = 0;

void loopClock() {
  unsigned long now = millis();

  if(overflowing && lastTime > now) {
    overflowing = false;
  }
  
  lastTime = now;
  
  if(!overflowing && now >= nextPhaseTime) {
    
    currentPhase = (currentPhase + 1) % MOON_PHASES;
    nextPhaseTime = nextPhaseTime + PHASE_DURATION * DAYS_TO_MS;
    overflowing = nextPhaseTime < now;
    
    debugln(String(now));
    debugln(String(nextPhaseTime));
    
    printPhase(currentPhase);
    
  } else {
    delay(1000);
  }
}
