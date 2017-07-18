//delcare buzzen pin
const int BUZZER_PIN = 8;

//
//declare the buzzer elements
//
const int  BUZZER_FREQ = 4200; //Hz,frequency of the buzzer sound
const unsigned long  BUZZER_DURATION = 80; //ms,duration of the buzzer sound
//const unsigned long BUZZER_DURATION = 300; //milliseconds,duration of the buzzer
//const unsigned long BUZZER_SOUND_DURATION = 100; //milliseconds,duration of the buzzer make sound
//const int  BUZZER_FREQ = 5000; //Hz,frequency of the buzzer sound


//the time of now
unsigned long now;

//the buzzer start time
unsigned long buzzerStartTime; //milliseconds

void setup() {
  Serial.begin(9600);//TODO for test
  // put your setup code here, to run once:
  pinMode(BUZZER_PIN, OUTPUT); //设置数字IO脚模式，OUTPUT为输出

  //  buzzer();
  //  delay(BUZZER_DURATION);
  //  buzzer();
}

void loop() {
  //  buzzer(2600);
  //  delay(2000);
  //  buzzer(4200);
  //  delay(2000);

  for (int i = 1; i <= 3; i++) {
    buzzer();
    delay(BUZZER_DURATION);
  }
  delay(3000);
  for (int i = 1; i <= 2; i++) {
    buzzer();
    delay(BUZZER_DURATION);
  }
  delay(3000);
  for (int i = 1; i <= 1; i++) {
    buzzer();
    delay(BUZZER_DURATION);
  }
  delay(3000);

  //  tone (BUZZER_PIN, BUZZER_FREQ);//sound

  //    for (int i = 2000; i <= 5000; i += 100) {
  //      Serial.println(i);//TODO for test
  //      tone (BUZZER_PIN, i);//sound
  //      delay(20);
  //      noTone(BUZZER_PIN);
  //      delay(2000);
  //    }

  // put your main code here, to run repeatedly:
  //  tone (BUZZER_PIN, BUZZER_FREQ);
  //  tone (BUZZER_PIN, BUZZER_FREQ, BUZZER_SOUND_DURATION);
  //  now = millis();
  //  if (now - buzzerStartTime >= BUZZER_DURATION) {
  //    buzzerStartTime = now;
  //    tone (BUZZER_PIN, BUZZER_FREQ);//sound
  //  } else if (now - buzzerStartTime <= BUZZER_SOUND_DURATION) {
  //    tone (BUZZER_PIN, BUZZER_FREQ); //sound
  //  } else if (now - buzzerStartTime > BUZZER_SOUND_DURATION) {
  //    noTone (BUZZER_PIN); //no sound
  //  } else {
  //    noTone (BUZZER_PIN); //no sound
  //  }


  //
  //  digitalWrite(buzzerPin, HIGH); //发声音
  //  delay(100);//延时1ms
  //  digitalWrite(buzzerPin, LOW); //不发声音
  //  delay(500);//延时ms

  //  for (int i = 0; i < 80; i++) //输出一个频率的声音
  //  {
  //    digitalWrite(buzzerPin, HIGH); //发声音
  //    delay(1);//延时1ms
  //    digitalWrite(buzzerPin, LOW); //不发声音
  //    delay(1);//延时ms
  //  }
  //  for (int i = 0; i < 100; i++) //输出另一个频率的声音
  //  {
  //    digitalWrite(buzzerPin, HIGH); //发声音
  //    delay(2);//延时2ms
  //    digitalWrite(buzzerPin, LOW); //不发声音
  //    delay(2);//延时2ms
  //  }
}

