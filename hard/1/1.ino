#define BUTTON 7
#define IN1 3
#define IN2 4
#define IN3 2
#define IN4  5
#define ENA 11
#define ENB 12

int speedMotor = 255;
bool statusButton
 void setup (){
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(BUTTON,INPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
 }

 void loop (){
  digitalWrite (IN1,HIGH);
  digitalWrite (IN2,LOW);
  digitalWrite (IN3,HIGH);
  digitalWrite (IN4,LOW);
  delay (3000);
  digitalWrite (IN1,LOW);
  digitalWrite (IN2,HIGH);
  digitalWrite (IN3,LOW);
  digitalWrite (IN4,HIGH);
  delay (3000);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(3000);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(3000);
 }
