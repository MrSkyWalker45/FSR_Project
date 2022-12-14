#include <LiquidCrystal.h>

#include <Wire.h>

int fsrPin1 = 0;     
int fsrReading1;     
int fsrVoltage1;     
long fsrResistance1;  
long fsrConductance1; 
long fsrForce1;      

const int trig_pin = 11;  
const int echo_pin = 12;
const int buzzer_pin = 10;


long duration; 
float cm; 

LiquidCrystal lcd(2,3,4,5,6,7);

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Clears the LCD screen
  lcd.clear();
  
  Serial.begin (9600);

  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  pinMode(buzzer_pin,OUTPUT);
    
}
 

void loop(void) {
  
  //For Sensor 1
  fsrReading1 = analogRead(fsrPin1); 
  fsrVoltage1 = map(fsrReading1, 0, 1023, 0, 5000);
    fsrResistance1= 5000 - fsrVoltage1;     // fsrVoltage is in millivolts so 5V = 5000mV             // 10K resistor
    fsrResistance1= fsrResistance1*10000;
    fsrResistance1= fsrResistance1/fsrVoltage1;
    fsrConductance1= 1000000;           // we measure in micromhos so 
    fsrConductance1= fsrConductance1/fsrResistance1;
    // Use the two FSR guide graphs to approximate the force
    if (fsrConductance1 <= 1000) {
      fsrForce1 = fsrConductance1 / 80;      
    } else {
      fsrForce1 = fsrConductance1 - 1000;
      fsrForce1 /= 30;         
    }
  Serial.print("fsrForce1: ");
  Serial.println(fsrForce1);
  
  //For Percentage Calculation
  
long force;
long totalweight;
float heavybus=5;

  force=fsrForce1;
  totalweight=force*0.10197;
  Serial.println(force);
long percentage;

percentage= totalweight/heavybus*100;
  
   Serial.println("Percentage: ");
  Serial.print(percentage);
  
    // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Capacity Used:");

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print(percentage);
    lcd.print(" %");

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
    delay(60);
}
