void setup() {
  Serial.begin(250000);
  Serial.println("hey");
  setup_cap();
  setup_light();
}


void loop() {
  Serial.println("k");
  struct cap_result s = getSense();
  Serial.println(s.mapped);
  light_rotate(s.mapped);
}
