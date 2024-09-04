// Este codigo es para que al apretar un boton en la protoboard ambos motores aumenten la velocidad.
//En cmabio si se apreta el otro motor que los motores vayan mas lento.

#define IN1 3
#define IN2 4
#define IN3 2
#define IN4 5
#define ENA 11
#define ENB 12

int speedMotor = 2;
bool statusLeft;
bool statusRight;
 void setup (){
  pinMode(IN1,OUTPUT);  // definiendo si entra o sale info
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  //encender motores
  digitalWrite (IN1,HIGH);
  digitalWrite (IN2,LOW);
  digitalWrite (IN3,HIGH);
  digitalWrite (IN4,LOW);
 }

 void loop (){
