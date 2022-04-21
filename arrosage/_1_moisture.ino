const int NB_CAPT = 4;
const int PINS[NB_CAPT] = {A0, A1, A2, A3}; 

int moistures[NB_CAPT];

String names[NB_CAPT] = {
  "Tanguy",
  "Biggy",
  "Boogy",
  "Baby"
};

void setupMoist() {
  for(int i=0; i<NB_CAPT; i++) {
    pinMode(PINS[i], INPUT);
  }
}

void readMoist() {
  for(int i=0; i<NB_CAPT; i++) {
    int rawInput = analogRead(PINS[i]);
    moistures[i] = mapMoist(rawInput);
    debug("[Input "); debug(String(i)); debug("] "); 
    debug("Raw: "); debug(String(rawInput)); debug(", "); 
    debug(String(moistures[i])); debug("%"); 
    debugln("");
  }
}

const int WET_INPUT = 260;
const int DRY_INPUT = 590;

int mapMoist(int analogInput) {
  return map(analogInput, DRY_INPUT, WET_INPUT, 0, 100);
}
