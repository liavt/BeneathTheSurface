#include <AFMotor.h>

AF_DCMotor front(1);
AF_DCMotor side(2);
AF_DCMotor top(3);
AF_DCMotor bottom(4);

const int ledPin=13;

void setup() {
 pinMode(ledPin,OUTPUT);
 Serial.begin(9600);

 side.run(RELEASE);
 front.run(RELEASE);
 top.run(RELEASE);
 bottom.run(RELEASE);
}

void runMotor(AF_DCMotor& mot, int input){
  /*
  String input;

  while(Serial.available()){
    char c = Serial.read();

    if(c == '\n'){
      break;  
    }

    input += c;
  }
  
  int output = input.toInt();*/
  
  if(input < 0){
    mot.run(BACKWARD);
    mot.setSpeed(-input);  
  }else{
    mot.run(FORWARD);  
    mot.setSpeed(input);
  }

  Serial.println(input);
}

void loop() {  
  while(Serial.available() > 0){
    int incomingByte = Serial.read();

    if(incomingByte == 'f'){
      runMotor(front, 255);
    }else if(incomingByte == 'b'){
      runMotor(front, -254);  
    }else if(incomingByte == 'r'){
      runMotor(side, 255);
    }else if(incomingByte == 'l'){
      runMotor(side, -254);
    }else if(incomingByte == 'c'){
      runMotor(side, 0);
    }else if(incomingByte == 's'){
      runMotor(front, 0);
    }else if(incomingByte == 'u'){
      runMotor(top, 255);
    }else if(incomingByte == 'd'){
      runMotor(top, -254);
    }else if(incomingByte == 'n'){
      runMotor(top, 0);
    }
  }
}


