const float MOON_CYCLE_DURATION = 29.530588; // days

//const unsigned long DAYS_TO_MS = 24L * 60L * 60L * 1000L;
const unsigned long DAYS_TO_MS = 200L;

const int MOON_PHASES = 8;
const int DISPLAY_PRECISION = 4;

const int PINS_START = 9;

const float PHASE_DURATION = MOON_CYCLE_DURATION / MOON_PHASES;

const int PHASES[MOON_PHASES][DISPLAY_PRECISION] = {
  {LOW,LOW,LOW,LOW},
  {LOW,LOW,LOW,HIGH},
  {LOW,LOW,HIGH,HIGH},
  {LOW,HIGH,HIGH,HIGH},
  {HIGH,HIGH,HIGH,HIGH},
  {HIGH,HIGH,HIGH,LOW},
  {HIGH,HIGH,LOW,LOW},
  {HIGH,LOW,LOW,LOW}
};


int currentPhase = 0;
float startOffset = 0;

void setupClock() {
  
  for(int i=0; i<DISPLAY_PRECISION; i++) {
    pinMode(PINS_START + i, OUTPUT);
    digitalWrite(PINS_START + i, LOW);
  }
  
}

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
    int pin = PINS_START + i;
    int value = phaseArray[i];
    
    digitalWrite(pin, value);
  }
  
}

void loopClock() {

  printPhase(currentPhase);
  
  currentPhase = (currentPhase + 1) % MOON_PHASES;

  unsigned long wait = (PHASE_DURATION - startOffset) * DAYS_TO_MS;
  startOffset = 0;
  
  delay(wait);
  
}
