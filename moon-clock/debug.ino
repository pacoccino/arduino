boolean debugEnabled = false;

const int baudRate = 9600;

void enableDebug() {
  debugEnabled = true;
  
  Serial.begin(9600);
  Serial.println("Debug started");
}

void debug(String s) {
  if(!debugEnabled) return;
  Serial.print(s);
}

void debugln(String s) {
  if(!debugEnabled) return;
  Serial.println(s);
}
