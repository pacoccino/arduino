void setup() {
  setupDebug();
  setupScreen();

}

void loop() {
  readMoist();
  displayMoist();
  //displayCycle();
  delay(2000);
}
