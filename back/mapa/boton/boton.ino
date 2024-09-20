// Hecho a modo de prueba. Simula el mensaje que le llegaría del arduino cuando detecta una linea. En este caso, es con un botón, que manda mensaje cuando es apretado.
bool apretado = false;

void setup() {
  pinMode(2, INPUT);  
  Serial.begin(9600);
}

void loop() {
  int a = digitalRead(2);
  
  if (a == HIGH && !apretado) {
    delay(50);
    if (digitalRead(2) == HIGH) {
      Serial.println("Apretado");
      apretado = true;
    }
  }
  
  if (a == LOW && apretado) {
    delay(50);
    if (digitalRead(2) == LOW) {
      apretado = false;
    }
  }
}
