/**
 * Infrared sensor
 * 
 * 共有四个红外探头，对于每个探头来说：
 * 如果前面没有任何遮挡或者检测到黑线就返回HIGH（就是有些波没被反射回来）；
 * 如果前面有东西遮挡并且没有检测到黑线就返回LOW（就是波都被反射回来了）。
 */
const int infrared1Pin = 4; //红外探头IN1
const int infrared2Pin = 5; //红外探头IN2    
const int infrared3Pin = 6; //红外探头IN3
const int infrared4Pin = 7; //红外探头IN4

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the sensor's pin an input:
  pinMode(infrared1Pin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  //如果前面没有任何遮挡或者检测到黑线就返回HIGH（就是有些波没被反射回来）；如果前面有东西遮挡并且没有检测到黑线就返回LOW（就是波都被反射回来了）。
  int sensorState = digitalRead(infrared1Pin);
  // print out the state of the sensor:
  Serial.println(sensorState);
  delay(1);        // delay in between reads for stability
}
