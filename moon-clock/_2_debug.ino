void setupDebug() {
  if(DEBUG) {
    Serial.begin(9600);
    Serial.println("Debug started");
  }
}

void debug(String s) {
  if(!DEBUG) return;
  Serial.print(s);
}

void debugln(String s) {
  if(!DEBUG) return;
  Serial.println(s);
}
