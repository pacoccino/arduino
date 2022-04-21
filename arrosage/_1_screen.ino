// A5 SCK  I2C Clock
// A4 SDA  I2C Data

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setupScreen() {
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay();
  oled.setTextSize(1);         
  oled.setTextColor(WHITE);   
  oled.display();              
}

/*
int loadCycle = 0;

void displayCycle() {
  switch(loadCycle) {
    case 0:
      oled.drawRect(0, 15, 60, 40, WHITE);
      break;
    case 1:
      oled.drawTriangle(30, 15, 0, 60, 60, 60, WHITE);
      break;
    case 2:
      oled.drawCircle(0, 10, 0, WHITE);
      break;
  }
  
  oled.display();    
  loadCycle = (loadCycle + 1) % 3;
}
*/
