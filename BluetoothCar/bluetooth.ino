//bluetooth
//

//declare CMD
const char CMD_FORWARD = 'F'; //go forward
const char CMD_BACKWARD = 'B';  //go backward
const char CMD_LEFT = 'L';  //turn left
const char CMD_RIGHT = 'R'; //turn right
const char CMD_STOP = 'S';  //stop
const char CMD_AUTO = 'X';  //auto or free
const char CMD_LIGHT_B_ON = 'U'; //Back lights On
const char CMD_LIGHT_B_OFF = 'u'; //Back lights Off
const unsigned long CMD_CLEAR_TIME = 1000 ; //auto clear cmd time, in ms
unsigned long cmdStartTime; //cmd start time
boolean toUpper = false; //if need change cmd to upper

//Check if there is a valid Bluetooth command
//updates:  cmd
//updates:  hasCMD, isStopCMD, isFreeCMD, isBackLightOn
//updates:  cmdStartTime
void checkCMD() {
  if (Serial.available()) {
    char c = Serial.read();
    Serial.print(c);//TODO for test
    //parse cmd comes from bluetooth client ARM_VOICE which is based on google voice
    //received cmd format:  *cmd#
    if (c == '*') { // voice cmd start
      toUpper = true; //need to change cmd to upper letter
      Serial.println("  voice cmd start");//TODO for test
    } else if (c == '#') { // voice cmd end
      toUpper = false; //no need to change cmd to upper letter
      Serial.println("  voice cmd end");//TODO for test
    } else {  //common cmd
      if (toUpper) {
        cmd = toupper(c); //change char to upper letter
      } else {
        cmd = c;
      }
      Serial.println(cmd);//TODO for test
      hasCMD = (cmd == CMD_FORWARD || cmd == CMD_BACKWARD || cmd == CMD_LEFT || cmd == CMD_RIGHT || cmd == CMD_STOP || cmd == CMD_AUTO || cmd == CMD_LIGHT_B_ON || cmd == CMD_LIGHT_B_OFF);
      isStopCMD = (cmd == CMD_STOP);
      isFreeCMD = (cmd == CMD_AUTO);
      if (cmd == CMD_LIGHT_B_ON) {
        isBackLightOn = true;
      }
      if (cmd == CMD_LIGHT_B_OFF) {
        isBackLightOn = false;
      }
      if (hasCMD) {
        cmdStartTime = millis();
      }
    }
  } else {
    if (millis() - cmdStartTime >= CMD_CLEAR_TIME) {  //reach auto clear cmd time
      cmd = CMD_STOP;
      hasCMD = false;
      isStopCMD = false;
      isFreeCMD = false;
    } else {  //under auto clear cmd time
      //TODO
      //contiune last cmd a while
    }
  }
}

//get the drive direction from CMD
//depends on: cmd
//returns:  driveDierction value (forward/backward/left/right)
//return stop if invalid cmd
int getCMDDirection() {
  switch (cmd) {
    case CMD_FORWARD:
      return DRIVE_DIRECTION_FORWARD;
    case CMD_BACKWARD:
      return DRIVE_DIRECTION_BACKWARD;
    case CMD_LEFT:
      return DRIVE_DIRECTION_LEFT;
    case CMD_RIGHT:
      return DRIVE_DIRECTION_RIGHT;
    default : //incorrect driving direction
      return DRIVE_DIRECTION_STOP;
  }
}
