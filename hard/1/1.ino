#define ENA 10 //velocidad mot izq 
#define ENB 11  // velocidad mot der
#define IN1 2   //direccion motor izq
#define IN2 3  
#define IN3 4   //direccion motor der
#define IN4 5   
#define TRIG1 7 
#define ECHO1 A1
#define TRIG2 8
#define ECHO2 A0   
#define INTERVALO 100  
#define SOUND_SPEED 0.034 
#define DISTANCIA_MINIMA 75
#define IR1 A2 // gris
#define IR4 A5 // negro
#define IR2 A3 // negro
#define IR3 A4 // gris

int velocidadena = 255;
int velocidadCorreccion = 10;
int velocidadenb = 65;
int velocidadmin = 0;
unsigned long medicionAnterior = 0;
const long intervalo = 200;
unsigned long tiempoAnterior = 0;
bool direccion = true; // true = adelante, false = atrás

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

  detenerRobot();
}

void loop() {
 
  // Escuchar comandos desde el puerto serie
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command == "ADELANTE") {
      moverAdelante();
    } else if (command == "ATRAS") {
      moverAtras();
    } else if (command == "LLEGASTE"){
      detenerRobot();
      }
  }

  IR();  

  if (millis() - medicionAnterior >= intervalo) {
    medicionAnterior = millis();
    float distancia = medirDistancia(direccion ? TRIG1 : TRIG2, direccion ? ECHO1 : ECHO2);

    Serial.print("Distancia ");
    Serial.print(direccion ? "Frontal: " : "Trasera: ");
    Serial.print(distancia);
    Serial.println(" cm");

    if (distancia <= DISTANCIA_MINIMA) {
      Serial.println("Obstáculo detectado. Deteniendo robot.");
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
  int valoresIR[4] = {analogRead(IR1), analogRead(IR2), analogRead(IR3), analogRead(IR4)};
  bool derechaClara = valoresIR[0] >= 900 && valoresIR[2] >= 900;  
  bool izquierdaOscura = valoresIR[1] > 100 && valoresIR[3] > 100; 
  
  if (derechaClara && !izquierdaOscura) { // Ambos sensores derechos detectan línea
    direccion ? moverAdelante() : moverAtras();
  } else if (izquierdaOscura) { // Ambos sensores izquierdos detectan fuera de línea
    direccion ? correccionIzquierda() : correccionDerecha();
  } else if (!derechaClara) { // Ambos sensores derechos detectan fuera de línea
    direccion ? correccionDerecha() : correccionIzquierda();
  } else {
    detenerRobot();
    Serial.println("Los sensores infrarrojos funcionan mal");
  }
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
