//Este codigo e para saber los valores del piso

#define IR1 A2 // gris
#define IR2 A3 // negro
#define IR3 A4 // gris
#define IR4 A5 // negro
unsigned long tiempoAnterior = 0;
const long intervalo = 200;

void setup() {
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
 Serial.begin(9600); 
}

void loop() {
   unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;
  }

  int valorIR1 = analogRead(IR1);  
  int valorIR2 = analogRead(IR2);  
  int valorIR3 = analogRead(IR3);  
  int valorIR4 = analogRead(IR4);  

  Serial.print("IR1: "); Serial.println(valorIR1);
  Serial.print("IR2: "); Serial.println(valorIR2);
  Serial.print("IR3: "); Serial.println(valorIR3);
  Serial.print("IR4: "); Serial.println(valorIR4);

}
