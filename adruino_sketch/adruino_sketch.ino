#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

String completeMessage = "";

void setup() {
  Serial.begin(115200);

  AFMS.begin();
  myMotor->setSpeed(150);
}

void loop() {
  char incomingByte = Serial.read();
  int checkByte = (int)incomingByte;

  if (checkByte == -1) {
    if(completeMessage != ""){
    String command = completeMessage.substring(0,1);
    int value = completeMessage.substring(1).toInt();

    if(command == "S"){
       myMotor->setSpeed(value);

       Serial.print("Set speed to: ");
       Serial.println(value);
    }else if(command == "A"){
        if(value == 1){
          myMotor->run(FORWARD);
        }else{
          myMotor->run(RELEASE);
        }
    }else{
        myMotor->run(RELEASE);
    }

    completeMessage = "";
    }
  } else {
    if (checkByte != -1) {
      completeMessage += incomingByte;
    }
  }
}
