int RECV_PIN = 11; //define input pin on Arduino
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RECV_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //  Serial.println(results.value, HEX);
  Serial.println(digitalRead(RECV_PIN));
  delay(1000);


}
