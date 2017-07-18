//
//declare the buzzer elements
//
//const int  BUZZER_FREQ = 2600; //Hz,frequency of the buzzer sound
//const unsigned long  BUZZER_DURATION = 50; //ms,duration of the buzzer sound

//buzzer alarm a little while
//delay was used here
void buzzer() {
  tone (BUZZER_PIN, BUZZER_FREQ);//buzzer alarm
  delay(BUZZER_DURATION);//alarm a little while
  noTone(BUZZER_PIN);//buzzer alarm cancel
}

void buzzer(int freq) {
  tone (BUZZER_PIN, freq);//buzzer alarm
  delay(BUZZER_DURATION);//alarm a little while
  noTone(BUZZER_PIN);//buzzer alarm cancel
}

