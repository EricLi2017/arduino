int num = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) //if or while
  {
    char c = Serial.read();
    //parse cmd comes from bluetooth client ARM_VOICE which is based on google voice
    //received cmd format:  *cmd#
    if (c == '*' || c == '#') {
      return; //ignor and return to next loop
    }
    //    if (c == 'A')
    //    {
    //      num++;
    //      Serial.print("Hello:num=");
    //      Serial.println(num);
    //    }
    num++;
    Serial.print(num);
    Serial.print(" ");
    Serial.print(c);
    Serial.print(" - ");//TODO for test
    c = toupper(c);
    Serial.println(c);//TODO for test



    //    delay(800);//delay会导致蓝牙发过来的命令排队
  }
}
