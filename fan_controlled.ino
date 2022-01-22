#include <LiquidCrystal.h>
#include "DHT.h" 
LiquidCrystal lcd(12, 11,5, 4, 3, 2);
int fan = 9;   // the pin where fan is
int tempMin = 5;   // the temperature to start the fan
int tempMax = 40;   // the maximum temperature when fan is at 100%
int fanSpeed;
int fanLCD=0;       // display the fan speed
#define DHTPIN 6 
#define DHTTYPE DHT11  
DHT sensor(DHTPIN, DHTTYPE); 
 
void setup() {
  // put your setup code here, to run once:
  pinMode(fan, OUTPUT);
  pinMode(DHTPIN, INPUT);
  lcd.begin(16,2);  
  lcd.setCursor(0,0);
  lcd.print(" WELCOME");
  delay(2000);
  sensor.begin();
  lcd.clear();
}


void loop() {
  // put your main code here, to run repeatedly:
  int temp = int(sensor.readTemperature());
//  float f = sensor.readTemperature(true);
   if (isnan(temp)) {
      lcd.print("E");
      delay(100);
      return;
  }
   if((temp >= tempMin) && (temp <= tempMax)) {  // if temperature is higher than minimum temp
       fanSpeed = map(temp, tempMin, tempMax, 32, 255); // the actual speed of fan
       fanLCD = map(temp, tempMin, tempMax, 0, 100);  // speed of fan to display on LCD
       analogWrite(fan, fanLCD` );  // spin the fan at the fanSpeed speed
   } 
   if(temp < tempMin) {   // if temp is lower than minimum temp
    fanSpeed = 0;      // fan is not spinning
    fanLCD = 0; 
    digitalWrite(fan, LOW);       
   } 
   if(temp > tempMax) {        // if temp is higher than tempMax
    digitalWrite(fan, HIGH); 
   } 
   lcd.setCursor(0,0);
   lcd.print("Temp:");
   lcd.print(temp); // display the temperature
//   lcd.write(223);//prints the degree symbol
//   lcd.print("C");
   lcd.setCursor(0,1); // move cursor to next line
   lcd.print("Fan Speed:");
   lcd.print(fanLCD); // display the fan speed
   lcd.print("%");
   //lcd.print(f);
   delay(2000);
}
