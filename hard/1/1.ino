#define ENA 10  
#define ENB 11  
#define IN1 3   
#define IN2 4  
#define IN3 2   
#define IN4 5   
#define TRIG1 7 
#define ECHO1 A1
#define TRIG2 8
#define ECHO2 A0   
#define INTERVALO 100  
#define SOUND_SPEED 0.034 
#define DISTANCIA_MINIMA 75
#define IR1 A2 // gris
#define IR2 A3 // negro
#define IR3 A4 // gris
#define IR4 A5 // negro

int velocidadmax = 255;
int velocidadmed = 125;
int velocidadmin = 0;
unsigned long medicionAnterior = 0;
const long intervalo = 200;
unsigned long tiempoAnterior = 0;
bool direccion;

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
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  
  Serial.begin(9600);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmin); 
  analogWrite(ENB, velocidadmin); 
}

void loop() {
  IR();
  
  // Verificar la dirección del robot
  if (digitalRead(IN1) == HIGH && digitalRead(IN2) == LOW && digitalRead(IN3) == HIGH && digitalRead(IN4) == LOW) {
    direccion = true;  // Movimiento hacia adelante
  } else if (digitalRead(IN1) == LOW && digitalRead(IN2) == HIGH && digitalRead(IN3) == LOW && digitalRead(IN4) == HIGH) {
    direccion = false;  // Movimiento hacia atrás
  }

  if (millis() - medicionAnterior >= intervalo) {
    medicionAnterior = millis();
    float distancia = 0;

    if (direccion) {
      distancia = medirDistancia(TRIG1, ECHO1);  // Sensor frontal
      Serial.print("Distancia Sensor Frontal: ");
    } else {
      distancia = medirDistancia(TRIG2, ECHO2);  // Sensor trasero
      Serial.print("Distancia Sensor Trasero: ");
    }

    Serial.print(distancia);
    Serial.println(" cm");

    if (distancia <= DISTANCIA_MINIMA) {
      Serial.println("Advertencia: Distancia demasiado corta. ¡Frenar!");
      detenerRobot();
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
  float distancia = duracion * SOUND_SPEED / 2;
  return distancia;
}

void detenerRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmin); 
  analogWrite(ENB, velocidadmin);
}

void IR() {
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

  // Verificar los valores de los sensores y mover el robot
  if (valorIR1 >= 300 && valorIR1 <= 320 && valorIR2 >= 300 && valorIR2 <= 320 && 
      valorIR3 < 300 && valorIR4 < 300) {
    // Todo está alineado, sigue recto
    moverAdelante();
  } else if (valorIR2 >= 300 && valorIR2 <= 320 && valorIR4 >= 300 && valorIR4 <= 320) {
    // IR2 e IR4 ven el gris (girar a la derecha)
    moverDerecha();
  } else if (valorIR1 >= 300 && valorIR1 <= 320 && valorIR3 >= 300 && valorIR3 <= 320) {
    // IR1 e IR3 ven el gris (girar a la izquierda)
    moverIzquierda();
  } else {
    // No detecta correctamente, detener
    detenerRobot();
    Serial.println("Los sensores infrarrojos no funcionan bien");
  }
}

void moverAdelante() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmax);
  analogWrite(ENB, velocidadmax);
}

void moverDerecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidadmax);
  analogWrite(ENB, velocidadmed); 
}

void moverIzquierda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmed); 
  analogWrite(ENB, velocidadmax);
}
