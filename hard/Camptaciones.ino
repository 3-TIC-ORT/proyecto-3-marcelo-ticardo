//Este codigo fue escrito por Chat, lo que le corregi fue que ahora no se comunica por puerto serie,
// y ahora la pista va a ser una franja negra en un fondo balco, los 4 sensores tienen q sensar negro
// Si alguno sensa blanco arranca a buscar la linea.
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

#define IR1 A2 // sensor1 (gris)
#define IR2 A3 // sensor2 (negro)
#define IR3 A4 // sensor3 (gris)
#define IR4 A5 // sensor4 (negro)

#define SOUND_SPEED 0.034 
#define DISTANCIA_MINIMA 75
#define INTERVALO 200

int velocidadena = 255;
int velocidadenb = 65;
int velocidadCorreccion = 90;
int velocidadmin = 0;

unsigned long medicionAnterior = 0;
bool direccion = true; // true = adelante, false = atrás

int umbralLinea = 700; // Ajustar según la calibración de los sensores

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

  detenerRobot();
}

void loop() {
  seguirLinea();

  if (millis() - medicionAnterior >= INTERVALO) {
    medicionAnterior = millis();
    float distancia = medirDistancia(direccion ? TRIG1 : TRIG2, direccion ? ECHO1 : ECHO2);

    if (distancia <= DISTANCIA_MINIMA) {
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

void seguirLinea() {
  int sensor1 = analogRead(IR1);
  int sensor2 = analogRead(IR2);
  int sensor3 = analogRead(IR3);
  int sensor4 = analogRead(IR4);

  bool s1 = sensor1 < umbralLinea;  // negro
  bool s2 = sensor2 < umbralLinea;
  bool s3 = sensor3 < umbralLinea;
  bool s4 = sensor4 < umbralLinea;

  // Si todos detectan negro, seguir
  if (s1 && s2 && s3 && s4) {
    moverAdelante();
  } else {
    buscarLinea();
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
  delay(200); // Pequeña pausa para evitar parpadeo extremo
}

void moverAdelante() {
  direccion = true;
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadena);
  analogWrite(ENB, velocidadenb);
}

void moverAtras() {
  direccion = false;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidadena);
  analogWrite(ENB, velocidadenb);
}

void detenerRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmin); 
  analogWrite(ENB, velocidadmin);
}

void correccionIzquierda() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadCorreccion);
  analogWrite(ENB, velocidadenb);
}

void correccionDerecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadena);
  analogWrite(ENB, velocidadCorreccion);
}
