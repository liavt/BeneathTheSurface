#include <AFMotor.h>

AF_DCMotor front(2);
AF_DCMotor right(4);
AF_DCMotor left(3);
AF_DCMotor top(1);

const int ledPin=13;

void setup() {
 pinMode(ledPin,OUTPUT);
 Serial.begin(9600);

 front.run(RELEASE);
 right.run(RELEASE);
 left.run(RELEASE);
 top.run(RELEASE);
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
  
  if(input == 0){
    mot.setSpeed(input);
    mot.run(RELEASE);
  }
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
    int instruction = Serial.read();
     
    /*
    f = front forward
    b = front backward
    s = front stop
    
    r = right forward
    e = right backward
    o = right stop
    
    l = left forward
    t = left backward
    a = left stop
    
    u = top forward
    d = top backward
    n = top stop
    */
    
    if(instruction == 'f'){
      runMotor(front, 255);
    }else if(instruction == 'b'){
      runMotor(front, -254);
    }else if(instruction == 's'){
      runMotor(front, 0);
    }else if(instruction == 'r'){
      runMotor(right, 255);
    }else if(instruction == 'e'){
      runMotor(right, -254);
    }else if(instruction == 'o'){
      runMotor(right, 0);
    }else if(instruction == 'l'){
      runMotor(left, -254);
    }else if(instruction == 't'){
      runMotor(left, 255);
    }else if(instruction == 'a'){
      runMotor(left, 0);
    }else if(instruction == 'u'){
      runMotor(top, 255);
    }else if(instruction == 'd'){
      runMotor(top, -254);
    }else if(instruction == 'n'){
      runMotor(top, 0);
    }
    
  }
}


