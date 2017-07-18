void carRun() {
  //  switch (driveDirection) {
  //    case DRIVE_DIRECTION_FORWARD:
  //      {
  //        //        Serial.println("  go forward");//TODO for test
  //        goForward();
  //      }
  //      break;
  //    case DRIVE_DIRECTION_BACKWARD:
  //      {
  //        //        Serial.println("  go backward");//TODO for test
  //        goBackward();
  //      }
  //      break;
  //    case DRIVE_DIRECTION_LEFT:
  //      {
  //        //        Serial.println("  turn left");//TODO for test
  //        turnLeft();
  //      }
  //      break;
  //    case DRIVE_DIRECTION_RIGHT:
  //      {
  //        //        Serial.println("  turn right");//TODO for test
  //        turnRight();
  //      }
  //      break;
  //    case DRIVE_DIRECTION_STOP:
  //      {
  //        //        Serial.println("  stop");//TODO for test
  //        park();
  //      }
  //      break;
  //    default : //incorrect driving direction
  //      //      Serial.println("  incorrect driving direction");
  //      break; //do nothing;
  //  }
  Serial.print(now);
  Serial.print("  ");
  Serial.print(millis());
  Serial.println(" car run");//TODO for test
}

