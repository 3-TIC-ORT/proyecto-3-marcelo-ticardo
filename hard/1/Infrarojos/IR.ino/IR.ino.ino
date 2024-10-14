//al pasarle la mano por arriba al infrarrojo diga led prendiso por puerto serie y se ptrenda el led.
// cuando sacar la mano se paga el led y por puerto serie dice led apagado

#define IR 3
#define LED 13
unsigned long tiempoAnterior = 0; 
const long intervalo = 200;
void setup() {
  pinMode(IR,INPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  Serial.begin(9600);
}


void loop() {
  unsigned long tiempoActual = millis();

   if(tiempoActual - tiempoAnterior >= intervalo){
    tiempoAnterior = tiempoActual

    int valorIR = analogRead(IR);
    Serial.printIn(valorIR);
    }
}
