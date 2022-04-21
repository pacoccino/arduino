void displayMoist() {
  oled.clearDisplay();
 
  oled.setCursor(40, 0);    
  oled.println("CannaBite");
  
  for(int i=0; i<NB_CAPT; i++) {
    int line = 20 + 10*i;
    
    oled.setCursor(0, line);   
    oled.println(names[i]);
    
    oled.setCursor(95, line);
    int percent =  moistures[i];
    oled.println(String(percent));
    
    oled.setCursor(110, line);
    oled.println("%");
  }
  
  oled.display();              
}
