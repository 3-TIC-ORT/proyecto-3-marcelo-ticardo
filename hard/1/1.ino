int IN1= 3;
int IN2= 4;
int IN3= 2;
int IN4= 5;

 void setup (){
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
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
