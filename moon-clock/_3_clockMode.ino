const float MOON_CYCLE_DURATION = 29.530588; // days

const unsigned long DAYS_TO_MS = 24L * 60L * 60L * 1000L;
//const unsigned long DAYS_TO_MS = 200L; // For debug

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
float startOffset = 0;

void setClockStart(int startDay) { 
  currentPhase = floor(startDay / PHASE_DURATION);
  startOffset = fmod(startDay, PHASE_DURATION);

  debug("Phase duration: "); debugln(String(PHASE_DURATION));
  debug("Current phase: "); debugln(String(currentPhase));
  debug("Start offset: "); debugln(String(startOffset));
}

void printPhase(int phase) {
  
  const int *phaseArray = PHASES[phase];
  
  for(int i=0; i<DISPLAY_PRECISION; i++) {
    lightOne(i, phaseArray[i]);
  }
  
}

void loopClock() {

  printPhase(currentPhase);
  
  currentPhase = (currentPhase + 1) % MOON_PHASES;

  unsigned long wait = (PHASE_DURATION - startOffset) * DAYS_TO_MS;
  startOffset = 0;
  
  delay(wait);
  
}
