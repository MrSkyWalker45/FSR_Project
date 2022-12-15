#include<LiquidCrystal.h> 
#define a1 0 
#define a2 1023
#define forceValue1 0 
#define forceValue2 50

const int trig_pin = 12; 
const int echo_pin = 11; 
const int buzzer_pin = 10; 

LiquidCrystal lcd(2,3,4,5,6,7);

long duration;
float cm; 
int forceValue;
int p;

void readForce(){
  lcd.clear();
  uint16_t sensorValue;
  int percentage; 
  sensorValue = analogRead(A0);
  forceValue = map(sensorValue,a1,a2,forceValue1,forceValue2); 
  percentage = p * 100;
  Serial.println(forceValue);
  lcd.setCursor(0,1);
  lcd.print("Capacity:");
  lcd.setCursor(10,1);
  lcd.print(percentage);
  lcd.setCursor(0,0);
  lcd.print("Force:");
  lcd.print(forceValue);
  lcd.setCursor(9,0);
  lcd.print("N");
  _delay_ms(1000);
  
}

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();

  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  pinMode(buzzer_pin,OUTPUT);
  

}

void loop(){

     digitalWrite(trig_pin,LOW);
    delayMicroseconds(5);
    digitalWrite(trig_pin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin,LOW);

    duration = pulseIn(echo_pin,HIGH);
    cm = (duration /2 ) / 29.1; 
    Serial.print(cm);
    Serial.println("cm");
    delay(250);
    if(cm <=50 && cm >= 0){
        analogWrite(buzzer_pin,1000);
        _delay_ms(250);
        analogWrite(buzzer_pin,0);
        _delay_ms(250);
    }
    else{
        analogWrite(buzzer_pin,0);
    }
      readForce();

}

