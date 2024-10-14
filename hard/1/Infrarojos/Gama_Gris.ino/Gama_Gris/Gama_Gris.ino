#define IR A3
unsigned long tiempoAnterior = 0;
const long intervalo = 200;

void setup() {
  Serial.begin(9600);
  pinMode(IR, INPUT);
}

void loop() {
  unsigned long tiempoActual = millis();  

  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;  
    int valorIR = analogRead(IR);  
    Serial.println(valorIR);
  }
}
