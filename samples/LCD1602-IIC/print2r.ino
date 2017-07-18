//auto print 2 rows if indeed for 1602LCD
//depends on: object lcd
void print2r(const char c[]) {
  int len = strlen(c);
  //  Serial.print(c);
  //  Serial.print(" sizeof ");
  //  Serial.print(sizeof(c));
  //  Serial.print(" length ");
  //  Serial.println(len);
  //  Serial.println(msglen(c));
  if (16 >= len) {//less than 16 char
    //    Serial.println("<=16");
    lcd.print(c);
  } else { //more than 16 char
    //    Serial.println(">16");
    //print 1st row
    lcd.print(c);

    //print 2nd row
    lcd.setCursor(0, 1);//set cols 0, rows 1
    for (int i = 16; i < len; i++) {
      lcd.print(c[i]);
    }
  }
}

