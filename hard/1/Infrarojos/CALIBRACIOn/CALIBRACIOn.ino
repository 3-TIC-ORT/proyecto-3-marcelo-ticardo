unsigned long tiempoAnterior = 0;
const long intervalo = 200;
void setup() {
  pinMode (A2, INPUT);
Serial.begin (9600); 
}

void loop() {
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;
  }
  int IR = analogRead(A2);
 Serial.print("IR: "); Serial.println(IR);
}
