const int TrigPin = 2;
const int EchoPin = 3;
unsigned long pulseLength;//in microseconds
float cm;
void setup() {
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}
void loop() {
  //发一个10ms的高脉冲去触发TrigPin
  digitalWrite(TrigPin, LOW);
  delay(60); // suggested min period 60 ms
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);// at least 10 us
  digitalWrite(TrigPin, LOW);

  pulseLength = pulseIn(EchoPin, HIGH);//读取返回的高电平持续时间
  cm =  pulseLength / 58.0; //算成厘米 //直接就是保留两位小数了(除以58.0);如果是除以58，则后两位小数都是0.
  //  cm = (int(cm * 100.0)) / 100.0; //保留两位小数 //这种方式不对，可能产生负数
  Serial.print(cm);
  Serial.print("cm, pulse length: ");
  Serial.print(pulseLength);
  Serial.print(" microseconds ");
  Serial.println();
  delay(1000);
}



