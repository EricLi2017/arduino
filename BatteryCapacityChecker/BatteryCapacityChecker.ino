/*
  Battery Capacity Checker
  Uses Nokia 5110 Display
  Uses 1 Ohm power resister as shunt - Load can be any suitable resister or lamp

  YouTube Video: https://www.youtube.com/embed/qtws6VSIoYk

  http://AdamWelch.Uk

  Required Library - LCD5110_Graph.h - http://www.rinkydinkelectronics.com/library.php?id=47
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

#define gatePin 10
#define highPin A0
#define lowPin A1

boolean finished = false;
int printStart = 0;
int interval = 5000;  //Interval (ms) between measurements

float mAh = 0.0;
float shuntRes = 1.0;  // In Ohms - Shunt resistor resistance
//float voltRef = 4.71; // Reference voltage (probe your 5V pin)
float voltRef = 4.54; // Reference voltage (probe your 5V pin)
float current = 0.0;
float battVolt = 0.0;
float shuntVolt = 0.0;
//float battLow = 2.9;  //for 18650 3.0v-4.2v
float battLow = 1.1;  //for AA NiMH 1.1v-1.5v

unsigned long previousMillis = 0;
unsigned long millisPassed = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Battery Capacity Checker v1.1");
  Serial.println("battVolt   current     mAh");

  pinMode(gatePin, OUTPUT);
  digitalWrite(gatePin, LOW);

  lcd.begin();
  lcd.println("Battery Check");
  lcd.println("Please Wait");

  delay(2000);
}

void loop() {
  //  int val = analogRead(highPin); //TODO for test
  //  Serial.println(val); //TODO for test

  battVolt = analogRead(highPin) * voltRef / 1024.0;
  shuntVolt = analogRead(lowPin) * voltRef / 1024.0;

  //  Serial.print(battVolt); //TODO for test
  //  Serial.print("\t"); //TODO for test
  //  Serial.println(battVolt); //TODO for test

  if (battVolt >= battLow && finished == false)
  {
    digitalWrite(gatePin, HIGH);
    millisPassed = millis() - previousMillis;
    current = (battVolt - shuntVolt) / shuntRes;
    mAh = mAh + (current * 1000.0) * (millisPassed / 3600000.0);
    previousMillis = millis();

    lcd.clear();
    lcd.home();
    lcd.print(battVolt);
    lcd.print("v ");
    lcd.print(current);
    lcd.print("a");
    lcd.setCursor(0, 1);//set cols 0, rows 1
    lcd.print(mAh);
    lcd.print("mAh");

    Serial.print(battVolt);
    Serial.print("\t");
    Serial.print(current);
    Serial.print("\t");
    Serial.println(mAh);

    delay(interval);
  }
  if (battVolt < battLow)
  {
    digitalWrite(gatePin, LOW);

    finished = true;

    lcd.clear();
    lcd.home();
    lcd.print(battVolt);
    lcd.print("v ");
    lcd.print(mAh);
    lcd.print("mAh");
    lcd.setCursor(0, 1);//set cols 0, rows 1
    lcd.print("Complete");

    delay(interval * 2);
  }
}
