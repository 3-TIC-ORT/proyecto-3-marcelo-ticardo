int IN1= 3;
int IN2= 4;

 void setup (){
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
 }

 void loop (){
  digitalWrite (IN1,HIGH);
  digitalWrite (IN2,LOW);
  delay (3000);
  digitalWrite (IN1,LOW);
  delay (3000);
  
 }
