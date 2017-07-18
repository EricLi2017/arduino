/*
   VCC: DC 5V-20V
   GND: GND pin
   OUT: high 3.3V, low 0V
*/
const int I_PIN = A3; //infrared sensor out pin

int val = 0;           // variable to store the value read
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //  pinMode(I_PIN, INPUT_PULLUP );
  //  pinMode(I_PIN, INPUT );
}

void loop() {
  // put your main code here, to run repeatedly:
  //  Serial.print(millis());
  //  Serial.print(" : ");
  //  Serial.println(digitalRead(I_PIN));

  val = analogRead(I_PIN);    // read the input pin
  //  Serial.println(val);             // debug value
  Serial.println(val * 5.0 / 1024.0);         // debug value
  //  delay(1000);

}
