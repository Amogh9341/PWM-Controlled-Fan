#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(8, 9, 3, 4, 5, 6);
Servo myServo;
const int tempin = A0;
const int fanpin = 11;
const float lowtemp = 10.0;
const float hightemp = 50.0;
const float freezelevel = 0.0;
const float maxdeg = 90.0;
const float mindeg =0.0;
const int buzzer = 10;

void setup(){
  lcd.begin(16, 2);
  lcd.print("Temp: ");
  pinMode(tempin, INPUT);
  pinMode(buzzer, OUTPUT);
  myServo.attach(fanpin);
  Serial.begin(9600);
}

float toCel(float a){
  return ((a*5.0/1024.0)-0.5)*100.0;
}

float setdeg(float t){
  if(t<lowtemp){
    return mindeg;
  }
  else if(t>=lowtemp && t<=hightemp){
  	return map(t,lowtemp,hightemp,mindeg,maxdeg);
  }
  else{
    return maxdeg;
  }
}

void print(float t,float deg){
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  if(t<=freezelevel) {
    tone(buzzer, 440);
    lcd.print("freeze");
  }
  else if(t>freezelevel && t<=lowtemp) {
    tone(buzzer, 1000);
    lcd.print("cool");
  }
  else if(t>=lowtemp && t<=hightemp){
    noTone(buzzer);
    lcd.print(t);
    lcd.print("C");
  }
  else  {
    tone(buzzer, 2000+2000*(t-hightemp)/75);
    lcd.print("hot");
  }
  
  lcd.setCursor(0, 1);
  lcd.print("Fan Speed:");
  lcd.print((int)deg*100/maxdeg);
  lcd.print("%");
  delay(1000);
  lcd.clear();
 
}
void loop(){
  myServo.write(0);
  float input = analogRead(tempin);
  float temp = toCel(input);
  int deg = setdeg(temp);
  myServo.write(deg);
  print(temp,deg);
}