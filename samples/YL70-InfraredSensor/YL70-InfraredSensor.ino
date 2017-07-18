/**
   Infrared sensor

   共有四个红外探头，对于每个探头来说：
   如果前面没有任何遮挡或者检测到黑线就返回HIGH（就是有些波没被反射回来）；
   如果前面有东西遮挡并且没有检测到黑线就返回LOW（就是波都被反射回来了）。
*/

//declare infrared sensor pins
//from left to right
const int INFRARED_1_PIN = 4; //infrared sensor 1:  IN4
const int INFRARED_2_PIN = 5; //infrared sensor 2:  IN3
const int INFRARED_3_PIN = 6; //infrared sensor 3:  IN2
const int INFRARED_4_PIN = 7; //infrared sensor 4:  IN1

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the sensor's pins input:
  pinMode(INFRARED_1_PIN, INPUT);
  pinMode(INFRARED_2_PIN, INPUT);
  pinMode(INFRARED_3_PIN, INPUT);
  pinMode(INFRARED_4_PIN, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  //如果前面没有任何遮挡或者检测到黑线就返回HIGH（就是有些波没被反射回来）；如果前面有东西遮挡并且没有检测到黑线就返回LOW（就是波都被反射回来了）。
  //  int sensorState = digitalRead(infrared1Pin);
  // print out the state of the sensor:
  //  Serial.println(digitalRead(INFRARED_IN1_PIN));
  //    Serial.println("IN1:"+digitalRead(INFRARED_IN1_PIN));
  //    Serial.println("IN2:"+digitalRead(INFRARED_IN2_PIN));
  //    Serial.println("IN3:"+digitalRead(INFRARED_IN3_PIN));
  //    Serial.println("IN4:"+digitalRead(INFRARED_IN4_PIN));

  Serial.print("IN1:");
  Serial.println(digitalRead(INFRARED_1_PIN));
  Serial.print("IN2:");
  Serial.println(digitalRead(INFRARED_2_PIN));
  Serial.print("IN3:");
  Serial.println(digitalRead(INFRARED_3_PIN));
  Serial.print("IN4:");
  Serial.println(digitalRead(INFRARED_4_PIN));

  Serial.println("---------------------------------------------------------");

  delay(1000);        // delay in between reads for stability
}
