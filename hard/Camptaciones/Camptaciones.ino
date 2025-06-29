// Motores y Puente H
#define ENA 10  
#define ENB 11  
#define IN1 3   // motor izquierdo
#define IN2 4
#define IN3 2   // motor derecho
#define IN4 5

// Ultrasonicos
#define TRIG1 7
#define ECHO1 A0
#define TRIG2 8
#define ECHO2 A1
#define INTERVALO 100
#define SOUND_SPEED 0.034
#define DISTANCIA_MINIMA 75

// Infrarrojos
#define IR1 A2 // sensor derecha delantera
#define IR2 A3 // sensor izquierda delantera
#define IR3 A4 // sensor derecha trasera
#define IR4 A5 // sensor izquierda trasera

int velocidadIzquierda = 255;   // Lo tengo que corregir
int velocidadDerecha = 65;      // Lo tengo que corregir
int velocidadCorreccion = 90;
int velocidadMax = 255;
int velocidadMinima = 0;

unsigned long UltimaMedicion = 0;
bool direccion = true;
bool obstaculoDetectado = false;

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IR1, INPUT); pinMode(IR2, INPUT);
  pinMode(IR3, INPUT); pinMode(IR4, INPUT);
  pinMode(TRIG1, OUTPUT); pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT); pinMode(ECHO2, INPUT);

  Serial.begin(9600);  
  detenerRobot();
}

void loop() {
  if (!obstaculoDetectado) {
    direccion ? moverAdelante() : moverAtras();
  }

  if (millis() - UltimaMedicion >= INTERVALO) {
    UltimaMedicion = millis();
    float distancia = medirDistancia(direccion ? TRIG1 : TRIG2, direccion ? ECHO1 : ECHO2);

    Serial.print(direccion ? "Distancia Sensor Frontal: " : "Distancia Sensor Trasero: ");
    Serial.print(distancia);
    Serial.println(" cm");

    if (distancia <= DISTANCIA_MINIMA) {
      detenerRobot();
      obstaculoDetectado = true;
    } else if (obstaculoDetectado) {
      obstaculoDetectado = false;
    }
  }

  seguirLinea();
}

float medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duracion = pulseIn(echoPin, HIGH);
  return duracion * SOUND_SPEED / 2;
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

