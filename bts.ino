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

void runMotor(AF_DCMotor& mot){
  String input;

  while(Serial.available()){
    char c = Serial.read();

    if(c == '\n'){
      break;  
    }

    input += c;
  }
  
  int output = input.toInt();
  
  if(output < 0){
    mot.run(BACKWARD);
    mot.setSpeed(output);  
  }else{
    mot.run(FORWARD);  
    mot.setSpeed(output);
  }

//  Serial.println(input);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  
  while(Serial.available() > 0){
    int incomingByte = Serial.read();

    if(incomingByte == 'f'){
      runMotor(front);
    }else if(incomingByte == 's'){
      runMotor(side);  
    }else if(incomingByte == 't'){
      runMotor(top);
    }else if(incomingByte == 'b'){
      runMotor(bottom);
    }
  }

  digitalWrite(ledPin, LOW);

  delay(10);
}
