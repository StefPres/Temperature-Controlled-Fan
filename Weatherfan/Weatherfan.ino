#include "DHT.h"           // Including DHT22 library
#include "LiquidCrystal.h" // Including LCD library

#define DHTPIN 6      // Declaring pin 6 for communicating to DHT22 sensor
#define DHTTYPE DHT22 // Declaring the type of DHT sensor we are using (DHT22 or DHT11)

DHT dht(DHTPIN, DHTTYPE);          // Declaring DHT connection and type
LiquidCrystal lcd(12,11,10,9,8,7); // Declaring LCD connections

int Motor_Pin1 = 4;  // pin 2 on L293D
int Motor_Pin2 = 3;  // pin 7 on L293D
int Enable = 5;      // pin 1 on L293D

void setup() {
  pinMode(Motor_Pin1, OUTPUT);  
  pinMode(Motor_Pin2, OUTPUT);
  pinMode(Enable, OUTPUT);
  lcd.begin(16,2); // Initializes the 16x2 LCD
  dht.begin();     // Initializes DHT sensor
}

void loop() {
  lcd.clear();                        // Clear LCD

  float temp = dht.readTemperature(); // Reading the temperature in Celsius

  if (isnan(temp)) {                  // Validating received data
    lcd.print("Failed to read");
    delay(1000);
    return;
  }

  lcd.setCursor(0,0);
  lcd.print("Temp.: "); 
  lcd.print(temp);      // Writing temperature in the first row
  lcd.print(" C");
  lcd.setCursor(0,1);   // Setting the position to display fan speed

  if(temp <15 ) {                 // If the temperature less than 25
    analogWrite(Enable,0);        // 0% PWM duty cycle
    lcd.print("Fan OFF ");      
    delay(100);
  }
  else if(temp>=15 & temp<30) {      // If the temperature is between 25 & 30
    analogWrite(Enable, 77);         // 30% of maximum duty cycle value (255). 
    lcd.print("Fan Speed: 30% ");
    delay(100);
  }
  else if(temp>=30 & temp<35) {      // If the temperature is between 30 & 35
    analogWrite(Enable, 153);        // 60% of maximum duty cycle value (255).
    lcd.print("Fan Speed: 60% ");
    delay(100);
  }
  else if(temp>=35) {                // If the temperature is above 35
    analogWrite(Enable, 255);        // 100% duty cycle
    lcd.print("Fan Speed: 100%   ");
    delay(100);
  }

  digitalWrite(Motor_Pin1, LOW);  // To drive the motor in a particular direction
  digitalWrite(Motor_Pin2, HIGH); // To drive the motor in a particular direction

  delay(2000); // 2 seconds delay
}
