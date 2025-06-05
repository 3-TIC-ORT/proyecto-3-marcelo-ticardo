//Este codigo fue escrito por Chat, lo que le corregi fue que ahora no se comunica por puerto serie,
// y ahora la pista va a ser una franja negra en un fondo balco, los 4 sensores tienen q sensar negro
// Si alguno sensa blanco arranca a buscar la linea.
// LINK A CHAT: https://chatgpt.com/c/6840d294-f654-800c-b4aa-df2b874bc869
#define ENA 10  // velocidad mot izq
#define ENB 11  // velocidad mot der
#define IN1 3   // motor izq
#define IN2 4  //motor
#define IN3 2   //motor der
#define IN4 5   //motor
#define TRIG1 7 
#define ECHO1 A1
#define TRIG2 8
#define ECHO2 A0   

#define IR1 A2 // sensor1 
#define IR2 A3 // sensor2 
#define IR3 A4 // sensor3 
#define IR4 A5 // sensor4 

#define SOUND_SPEED 0.034 
#define DISTANCIA_MINIMA 75
#define INTERVALO 200

int velocidadena = 255; // ESTOS 2 LOS TENGO QUE CAMBIAR PQ LOS MOTORES SEGURO SON DIFERENTES
int velocidadenb = 65;
int velocidadCorreccion = 90;
int velocidadmin = 0;

unsigned long medicionAnterior = 0;
bool direccion = true; // true = adelante, false = atrás

int umbralLinea = 700; // TENGO QUE PONER EL VALOR DEL NEGRO

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(TRIG1, OUTPUT); pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT); pinMode(ECHO2, INPUT);
  pinMode(IR1, INPUT); pinMode(IR2, INPUT);
  pinMode(IR3, INPUT); pinMode(IR4, INPUT);

  detenerRobot();
}

void loop() {
  seguirLinea();

  if (millis() - medicionAnterior >= INTERVALO) { // si ya paso el tiempo de intervalo q vuelva a corre el if
    medicionAnterior = millis();
    float distancia = medirDistancia(direccion ? TRIG1 : TRIG2, direccion ? ECHO1 : ECHO2); // Si direccion es true, usa TRIG1. Si direccion es false, usa TRIG2.
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
