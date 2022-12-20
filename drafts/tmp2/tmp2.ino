void setup() {
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);

  Serial.begin(9600);
}

int mode = LOW;
int intensity = 0;

void loop() {

  int diode = analogRead(A0);
  analogWrite(6, diode);

  Serial.println(String(diode));

  /*
  analogWrite(6, intensity);
  intensity = intensity + 10;
  if(intensity > 255) {
    intensity = 0;
  }
  
  digitalWrite(10, mode);
  
  if(mode == LOW) {
    mode = HIGH;
  } else {
    mode = LOW;
  }
  delay(1000);
  */
}
