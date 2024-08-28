#define BUTTONRIGHT 7
#define BUTTONLEFT 8
#define IN1 3
#define IN2 4
#define IN3 2
#define IN4 5
#define ENA 11
#define ENB 12

int speedMotor = 255;
bool statusLeft;
bool statusRight;
 void setup (){
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(BUTTONRIGHT,INPUT);
  pinMode(BUTTONLEFT,INPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  //encender motor
  digitalWrite (IN1,HIGH);
  digitalWrite (IN2,LOW);
  digitalWrite (IN3,HIGH);
  digitalWrite (IN4,LOW);
 }

 void loop (){
  statusLeft = digitalRead (BUTTONLEFT);
  statusRight = digitalRead (BUTTONRIGHT);

  if(statusLeft == HIGH){
    if(speedMotor <= 0){
    speedMotor = 0;
    } else {
      speedMotor = speedMotor -5;
    } 
  }
     if(speedMotor >= 255){
      if(statusRight == HIGH){
      speedMotor = 255;
      } else {
      speedMotor = speedMotor +5;
      }
   }
   analogWrite(ENA,speedMotor);
   analogWrite(ENB,speedMotor);
   delay(150);
 }
