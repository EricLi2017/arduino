int ledDelay = 50; //delay by 50ms
int redPin = 10;
int bluePin = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(redPin, HIGH);
  delay(ledDelay);
  digitalWrite(redPin, LOW);
  delay(ledDelay);

  digitalWrite(redPin, HIGH);
  delay(ledDelay);
  digitalWrite(redPin, LOW);
  delay(ledDelay);

  digitalWrite(redPin, HIGH);
  delay(ledDelay);
  digitalWrite(redPin, LOW);
  delay(ledDelay);

  delay(100);

  digitalWrite(bluePin, HIGH);
  delay(ledDelay);
  digitalWrite(bluePin, LOW);
  delay(ledDelay);

  digitalWrite(bluePin, HIGH);
  delay(ledDelay);
  digitalWrite(bluePin, LOW);
  delay(ledDelay);

  digitalWrite(bluePin, HIGH);
  delay(ledDelay);
  digitalWrite(bluePin, LOW);
  delay(ledDelay);

//  delay(100);
}
