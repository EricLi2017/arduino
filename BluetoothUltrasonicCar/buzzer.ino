//buzzer
//

//buzzer alarm a little while
//delay was used here
void alarm() {
  tone (BUZZER_PIN, BUZZER_FREQ);//buzzer alarm
  delay(BUZZER_DURATION);//alarm a little while
  noTone(BUZZER_PIN);//buzzer alarm cancel
  delay(BUZZER_DURATION);//wait a little while
}

//buzzer alarm according to the setting times
//depends on: buzzerTimes
//delay was user here
void buzzer() {
  for (int i = 1; i <= buzzerTimes; i++) {
    alarm();
  }
}
