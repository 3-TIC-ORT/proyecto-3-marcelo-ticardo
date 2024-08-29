// Este codigo es para que al apretar un boton en la protoboard ambos motores aumenten la velocidad.
//En cmabio si se apreta el otro motor que los motores vayan mas lento.

#define BUTTONRIGHT 7  // definiendo cada variable con un pin digital
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
  pinMode(IN1,OUTPUT);  // definiendo si entra o sale info
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(BUTTONRIGHT,INPUT);
  pinMode(BUTTONLEFT,INPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  //encender motores
  digitalWrite (IN1,HIGH);
  digitalWrite (IN2,LOW);
  digitalWrite (IN3,HIGH);
  digitalWrite (IN4,LOW);
 }

 void loop (){
  statusLeft = digitalRead (BUTTONLEFT);
  statusRight = digitalRead (BUTTONRIGHT);

  if(statusLeft == HIGH){
    if(speedMotor <= 0){ // Si se apreta el boton de la derecha que la velociidad disminuya,
    speedMotor = 0;      //si la velocidad del motor =< 0, que el motor frene.
    } else {
      speedMotor = speedMotor -5;
    } 
  } 
     
     if(speedMotor >= 255){
      if(statusRight == HIGH){ // Si se apreta el boton izquierdo que la velocidad aumente de 5 en 5.
      speedMotor = 255;        // Si la velocidad de los motores <= 255, que se quede en 255
      } else {
      speedMotor = speedMotor +5;
      }
   } 
   analogWrite(ENA,speedMotor);
   analogWrite(ENB,speedMotor);
   delay(150);
 }