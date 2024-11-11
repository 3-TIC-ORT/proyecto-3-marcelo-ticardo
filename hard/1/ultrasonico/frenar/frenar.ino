#define TRIG1 7 
#define ECHO1 A0
#define TRIG2 8
#define ECHO2 A1  
#define INTERVALO 100  
#define SOUND_SPEED 0.034 
#define DISTANCIA_MINIMA 30
#define ENA 10  
#define ENB 11  
#define IN1 3 
#define IN2 4   
#define IN3 2   
#define IN4 5   

int velocidadmax = 255; 
int velocidadmin = 0;
unsigned long UltimaMedicion = 0;
bool direccion = true;  
bool obstaculoDetectado = false;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command == "ADELANTE") {
      moverAdelante();
    } else if (command == "ATRAS") {
      moverAtras();
    } 
    
  }
  
  if (millis() - UltimaMedicion >= INTERVALO) {
    UltimaMedicion = millis();
    float distancia = medirDistancia(direccion ? TRIG1 : TRIG2, direccion ? ECHO1 : ECHO2);
    if (distancia <= DISTANCIA_MINIMA) {
      detenerRobot();
      obstaculoDetectado = true;
    } else if (obstaculoDetectado) {
      obstaculoDetectado = false;
      direccion ? moverAdelante() : moverAtras();
    }
  }
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

void detenerRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmin); 
  analogWrite(ENB, velocidadmin);
}

void moverAdelante() {
  direccion = true;
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmax);
  analogWrite(ENB, velocidadmax);
}

void moverAtras() {
  direccion = false;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidadmax);
  analogWrite(ENB, velocidadmax);
}
