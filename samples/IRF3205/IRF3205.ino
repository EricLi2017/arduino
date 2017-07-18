#define gatePin 10

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
//  Serial.println("Battery Capacity Checker v1.1");
//  Serial.println("battVolt   current     mAh");

  pinMode(gatePin, OUTPUT);
  digitalWrite(gatePin, LOW);
}

// the loop function runs over and over again forever
void loop() {
digitalWrite(gatePin, HIGH);
delay(1000);
digitalWrite(gatePin, LOW);
delay(1000);
}
