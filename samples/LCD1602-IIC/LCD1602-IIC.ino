#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
char msg[] = "Happy new year! 2017";
int i = 0;
void setup()
{
  //  Serial.begin(9600);

  lcd.begin();
  //  lcd.backlight();

  //  lcd.print(12);
  //  lcd.print("CM");
  //  lcd.autoscroll();
  //  lcd.print("Happy");
  //  lcd.print(" new");
  //  lcd.print(" year!");
  //  lcd.print("2017");

  //    lcd.print(msg);
  //  lcd.print("Hello, world!");
  //  lcd.print("Happy new year!2017");

  print2r(msg);
}


void loop()
{
//  lcd.home();
  if (i == 0) {
    lcd.noBacklight();
    //    print2r(msg);
    i = 1;
    delay(1000);
  } else {
    lcd.backlight();
    //    print2r(msg);
    i = 0;
    delay(1000);
  }

  //  lcd.clear();
  //  lcd.home();
  //  //  print2r(msg);
  //  if (i >= 120) {
  //    i = 0;
  //  }
  //  i++;
  //
  //  lcd.print(i);
  //  lcd.print("CM");

  //  lcd.print("Happy");
  //  lcd.print(" new");
  //  lcd.print(" year!");
  //  lcd.print("2017");
  //  delay(1000);
}

