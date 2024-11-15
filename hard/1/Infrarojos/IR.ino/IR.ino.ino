#define ENA 10  
#define ENB 11  
#define IN1 3   
#define IN2 4  
#define IN3 2   
#define IN4 5   
#define IR1 A2 
#define IR4 A5

#define IR2 A3 
#define IR3 A4 

unsigned long tiempoAnterior = 0;
const long intervalo = 200;
int velocidadmax = 255;
int velocidadCorreccion = 50;
int velocidadmin = 0;



void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
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

  if (valorIR1 < 100 && valorIR3 < 100 && valorIR2 > 500 && valorIR4 > 500) {
      moverAdelante();
  } else if (valorIR1 > 100 && valorIR3 > 100) {
    correccionDerecha();
  } else if (valorIR4 < 500 && valorIR2 < 500) {
    correccionIzquierda();
  }
}

void detenerRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmin);
  analogWrite(ENB, velocidadmin);
}

void moverAdelante() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmax);
  analogWrite(ENB, velocidadmax);
}

void moverAtras() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidadmax);
  analogWrite(ENB, velocidadmax);
}

void correccionIzquierda() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadCorreccion);
  analogWrite(ENB, velocidadmax);
}

void correccionDerecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmax);
  analogWrite(ENB, velocidadCorreccion);
}
  
