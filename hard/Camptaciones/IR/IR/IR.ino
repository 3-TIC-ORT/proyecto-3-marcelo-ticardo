// Motores y Puente H
#define ENA 10  
#define ENB 11  
#define IN1 3   // motor izquierdo
#define IN2 4
#define IN3 2   // motor derecho
#define IN4 5

// Infrarrojos
#define IR1 A2 // sensor derecha delantera
#define IR2 A3 // sensor izquierda delantera
#define IR3 A4 // sensor derecha trasera
#define IR4 A5 // sensor izquierda trasera

int velocidadIzquierda = 255;   //Corregir con las velocidades de los motores
int velocidadDerecha = 65;      
int velocidadCorreccion = 90;
int velocidadMinima = 0;

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IR1, INPUT); pinMode(IR2, INPUT);
  pinMode(IR3, INPUT); pinMode(IR4, INPUT);


  Serial.begin(9600);  
  detenerRobot();
}

void loop() {

  seguirLinea();
}

void seguirLinea() {
  int sensor1 = analogRead(IR1); // derecha delantera
  int sensor2 = analogRead(IR2); // izquierda delantera
  int sensor3 = analogRead(IR3); // derecha trasera
  int sensor4 = analogRead(IR4); // izquierda trasera

  // Si los 4 sensores detectan blanco seguir derecho
  if (sensor1 < 100 && sensor2 < 100 && sensor3 < 100 && sensor4 < 100) {
    moverAdelante();
  } else {
    buscarLinea();  // Si alguno ve negro, corregir
  }
}

void buscarLinea() {
  static bool giroIzquierda = true;
  if (giroIzquierda) {
    correccionIzquierda();
  } else {
    correccionDerecha();
  }
  giroIzquierda = !giroIzquierda;
  delay(200); // pequeña pausa para estabilidad
}

void moverAdelante() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadIzquierda);
  analogWrite(ENB, velocidadDerecha);
}

void moverAtras() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidadIzquierda);
  analogWrite(ENB, velocidadDerecha);
}

void detenerRobot() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadMinima); 
  analogWrite(ENB, velocidadMinima);
}

void correccionIzquierda() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadCorreccion);
  analogWrite(ENB, velocidadDerecha);
}

void correccionDerecha() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadIzquierda);
  analogWrite(ENB, velocidadCorreccion);
}

