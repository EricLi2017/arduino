/*
   VCC: 3.3V-5V
   GND: GND pin
   OUT: IO pin, value 0(sound),1(no sound)
*/
const int S_PIN = 3; //sound sensor out pin
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(S_PIN, INPUT );
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(millis());
  Serial.print(" : ");
  Serial.println(digitalRead(S_PIN));
  delay(1000);

}
