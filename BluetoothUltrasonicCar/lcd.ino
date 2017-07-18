//LCD 1602 with IIC/I2C
//

//LCD no backlight
void lcdOff() {
  lcd.noBacklight();
}
//LCD with backlight
void lcdOn() {
  lcd.backlight();
}
//LCD display front obstacle distance in 1st row
//depends on: cmFront
void lcdPrintFront() {
  lcd.clear();
  lcd.home();
  lcd.print(cmFront);
  lcd.print("CM");
}

//LCD display left and right obstacle distance in 2nd row
//depends on: cmLeft,cmRight
void lcdPrintSides() {
  lcd.setCursor(0, 1);//set cols 0, rows 1
  lcd.print("L");
  lcd.print(cmLeft);
  lcd.print("CM,");
  lcd.print("R");
  lcd.print(cmRight);
  lcd.print("CM");
}

//LCD display front and sides obstacle distance
//depends on: cmFront,cmRight,cmLeft
void lcdPrintAll() {
  lcdPrintFront();
  lcdPrintSides();
}

//LCD display message
void lcdPrint(char msg) {
  lcd.clear();
  lcd.home();
  lcd.print(msg);
}
//LCD display message
void lcdPrint(char msg[]) {
  lcd.clear();
  lcd.home();
  int len = strlen(msg);
  if (16 >= len) {//less than 16 char
    lcd.print(msg);
  } else { //more than 16 char
    //print 1st row
    lcd.print(msg);

    //print 2nd row
    lcd.setCursor(0, 1);//set cols 0, rows 1
    for (int i = 16; i < len; i++) {
      lcd.print(msg[i]);
    }
  }
}
