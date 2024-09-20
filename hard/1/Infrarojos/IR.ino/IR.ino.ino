//al pasarle la mano por arriba al infrarrojo diga hola por puerto serie

#define IR 3
#define LED 13
void setup() {
  pinMode(IR,INPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
}

void loop() {
  int estado = digitalRead(IR); 
 if(estado = LOW){
  digitalWrite(LED,HIGH);
  } else {
     digitalWrite(LED,LOW);
    }
}
