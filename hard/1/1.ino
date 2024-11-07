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
int velocidadCorreccion = 10;
int velocidadmed = 125;  // corregido aquí
int velocidadmin = 0;
unsigned long medicionAnterior = 0;
const long intervalo = 200;
unsigned long tiempoAnterior = 0;
bool direccion; // variable para dirección
unsigned long tiempoInicioGiro = 0;
bool girandoDerecha = false;
bool girandoIzquierda = false;
const unsigned long duracionGiro90 = 400;

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

  // Escuchar comandos desde el puerto serie
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Leer hasta un salto de línea
    if (command == "ADELANTE") {
      moverAdelante();
    } else if (command == "ATRAS") {
      moverAtras();
    } else if (command == "PARAR"){
      detenerRobot();
      }
  }

  // Resto del código para controlar el movimiento del robot

  if (millis() - medicionAnterior >= intervalo && !girandoDerecha && !girandoIzquierda) {
    medicionAnterior = millis();
    float distancia = 0;

    if (command == "ADELANTE") {
      distancia = medirDistancia(TRIG1, ECHO1);  
      Serial.print("Distancia Sensor Frontal: ");
    } else if (command == "ATRAS") {
      distancia = medirDistancia(TRIG2, ECHO2);  
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

 if (valorIR1 >= 900 && valorIR1 <= 1000 && valorIR3 >= 900 && valorIR3 <= 1000 && 
     valorIR2 >= 50 && valorIR4 <= 90) {
     if(command == "ADELANTE"){
      moverAdelante();
      } else if (command == "ATRAS"){
         moverAtras();
        }
  } else if (valorIR2 >= 100 && valorIR2 <= 1000 && valorIR4 >= 100 && valorIR4 <= 1000) {  
          if(command == "ADELANTE"){
            digitalWrite(IN1,HIGH);
            digitalWrite(IN2,LOW);
            digitalWrite(IN3,HIGH);
            digitalWrite(IN4,LOW);
            analogWrite(ENA, velocidadmed);
            analogWrite(ENB, velocidadCorreccion);
          } else if (command == "ATRAS"){
            digitalWrite(IN1,LOW);
            digitalWrite(IN2,HIGH);
            digitalWrite(IN3,LOW);
            digitalWrite(IN4,HIGH);
            analogWrite(ENA, velocidadmed);
            analogWrite(ENB, velocidadCorreccion);
          }
          
  } else if (valorIR1 <= 900 && valorIR3 <= 900) {
       if(command == "ADELANTE"){
            digitalWrite(IN1,HIGH);
            digitalWrite(IN2,LOW);
            digitalWrite(IN3,HIGH);
            digitalWrite(IN4,LOW);
            analogWrite(ENA, velocidadCorreccion);
            analogWrite(ENB, velocidadmed);
       } else if (command == "ATRAS"){
            digitalWrite(IN1,LOW);
            digitalWrite(IN2,HIGH);
            digitalWrite(IN3,LOW);
            digitalWrite(IN4,HIGH);
            analogWrite(ENA, velocidadCorreccion);
            analogWrite(ENB, velocidadmed);
       }
    
  } else {
    detenerRobot();
    Serial.println("Los sensores infrarrojos no funcionan bien");
  }
}

void moverAdelante(){
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);  
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   analogWrite(ENA,velocidadmed);  
   analogWrite(ENB,velocidadmed);  
}

void moverAtras(){
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);  
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
   analogWrite(ENA,velocidadmed);  
   analogWrite(ENB,velocidadmed);  
}
