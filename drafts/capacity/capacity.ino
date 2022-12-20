#include <CapacitiveSensor.h>
#include <AverageValue.h>


CapacitiveSensor cs = CapacitiveSensor(2,3);  
const long MAX_VALUES_NUM = 10;
AverageValue<long> av(MAX_VALUES_NUM);  

const unsigned int LED_R_PIN = 9;
const unsigned int LED_G_PIN = 6;
const unsigned int LED_B_PIN = 10;


struct RGB {
  byte r;
  byte g;
  byte b;
} ;

struct HSB {
  unsigned short h;
  byte s;
  byte b;
};

struct RGB hsb2rgb(struct HSB *hsb) {

  struct RGB rgb;

  int H = hsb->h % 360;
  int S = max(min(hsb->s, 100), 0);
  int B = max(min(hsb->b, 100), 0);

  float s = S/100;
  float v = B/100;
  float C = s*v;
  float X = C*(1-abs(fmod(H/60.0, 2)-1));
  float m = v-C;
  float r,g,b;
  if(H >= 0 && H < 60){
      r = C,g = X,b = 0;
  }
  else if(H >= 60 && H < 120){
      r = X,g = C,b = 0;
  }
  else if(H >= 120 && H < 180){
      r = 0,g = C,b = X;
  }
  else if(H >= 180 && H < 240){
      r = 0,g = X,b = C;
  }
  else if(H >= 240 && H < 300){
      r = X,g = 0,b = C;
  }
  else{
      r = C,g = 0,b = X;
  }
    
  rgb.r = (r+m)*255;
  rgb.g = (g+m)*255;
  rgb.b = (b+m)*255;

  return rgb;
}

void setup()                    
{

   cs.set_CS_AutocaL_Millis(0xFFFFFFFF); 
   
   cs.set_CS_Timeout_Millis(500);
   
   Serial.begin(9600);

   pinMode(LED_R_PIN, OUTPUT);
   pinMode(LED_G_PIN, OUTPUT);
   pinMode(LED_B_PIN, OUTPUT);

  pushColor(255);
}

int low = 500;
int high = 3000;

void loop()                    
{
    long start = millis();
    long total1 =  cs.capacitiveSensor(30);
    av.push(total1);

    long average = av.average();

    long kept = constrain(average, low, high);
  
    int pitch = map(kept, low, high, 50, 4000);
    unsigned short hue = map(kept, low, high, 0, 359);
 
    Serial.print(millis() - start);       
    Serial.print("\t");      
    Serial.print(String(total1));    
    Serial.print("\t");  
    Serial.print(String(average));       
    Serial.print("\t");  
    Serial.print(String(kept));        
    Serial.print("\t");  
    Serial.print(String(pitch));        
    Serial.print("\t");  
    Serial.print(String(hue));       
    Serial.print("\t");  
    Serial.println("");  

    pushColor(hue);
    tone(5, pitch, 500);
    
    delay(10);                           
}

void pushColor(unsigned short hue) {
  struct HSB hsb = { hue, 100, 100 };
  
  struct RGB rgb = hsb2rgb(&hsb);

/*
    Serial.print(rgb.r);       
    Serial.print("\t");      
    Serial.print(rgb.g);       
    Serial.print("\t");     
    Serial.println(rgb.b);    
*/
   analogWrite(LED_R_PIN, rgb.r);
   analogWrite(LED_G_PIN, rgb.g);
   analogWrite(LED_B_PIN, rgb.b);
}
