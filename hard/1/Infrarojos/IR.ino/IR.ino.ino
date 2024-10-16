
//al pasarle la mano por arriba al infrarrojo diga hola por puerto serie
//al pasarle la mano por arriba al infrarrojo diga led prendiso por puerto serie y se ptrenda el led.
// cuando sacar la mano se paga el led y por puerto serie dice led apagado

#define IR A2
#define LED 13

 void setup() {
  pinMode(IR,INPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  Serial.begin(9600);
}

void loop() {
  int estado = analogRead(IR); 

{}ñ 
 if(estado == HIGH){
  digitalWrite(LED,HIGH);
  Serial.println("Led apagado");
  } else {
     digitalWrite(LED,LOW);
     Serial.println("Led prendido");
    }
}
