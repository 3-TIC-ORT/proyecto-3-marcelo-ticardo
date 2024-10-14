#define IR A3
unsigned long medicionAnterior = 0;
const long intervalo = 200;

void setup() {
  Serial.begin(9600);
  pinMode(IR, INPUT);
}

void loop() {
  unsigned long medicionActual = millis();  

  if (medicionActual - medicionAnterior >= intervalo) {
    medicionAnterior = medicionActual;  
    int valorIR = analogRead(IR);  
    Serial.println(valorIR);
  }
}
