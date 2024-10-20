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

  if (!girandoDerecha && !girandoIzquierda) {
    if (digitalRead(IN1) == HIGH && digitalRead(IN2) == LOW && digitalRead(IN3) == HIGH && digitalRead(IN4) == LOW) {
      direccion = true;  
    } else if (digitalRead(IN1) == LOW && digitalRead(IN2) == HIGH && digitalRead(IN3) == LOW && digitalRead(IN4) == HIGH) {
      direccion = false;  
    }
  }

  if (millis() - medicionAnterior >= intervalo && !girandoDerecha && !girandoIzquierda) {
    medicionAnterior = millis();
    float distancia = 0;

    if (direccion) {
      distancia = medirDistancia(TRIG1, ECHO1);  
      Serial.print("Distancia Sensor Frontal: ");
    } else {
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

  if (girandoDerecha) {
    moverDerecha();
  } else if (girandoIzquierda) {
    moverIzquierda();
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

  if (valorIR1 >= 300 && valorIR1 <= 320 && valorIR3 >= 300 && valorIR3 <= 320 && 
      valorIR2 < 300 && valorIR4 < 300) {
    moverAdelante();
  } else if (valorIR2 >= 300 && valorIR2 <= 320 && valorIR4 >= 300 && valorIR4 <= 320) {
    girarDerecha90();
  } else if (valorIR1 >= 300 && valorIR1 <= 320 && valorIR3 >= 300 && valorIR3 <= 320) {
    girarIzquierda90();
  } else {
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

void moverAtras(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENA,velocidadmax);
  analogWrite(ENB,velocidadmax);
}

void girarDerecha90() {
  if (!girandoDerecha) {
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW);  
    digitalWrite(IN3, LOW);  
    digitalWrite(IN4, HIGH); 

    analogWrite(ENA, velocidadmax);  
    analogWrite(ENB, velocidadmax);  

    tiempoInicioGiro = millis(); 
    girandoDerecha = true; 
  } else {
    
    if (millis() - tiempoInicioGiro >= duracionGiro90) {
      detenerRobot(); 
      girandoDerecha = false; 
    }
  }
}

void girarIzquierda90() {
  if (!girandoIzquierda) {
    digitalWrite(IN1, LOW);  
    digitalWrite(IN2, HIGH); 
    digitalWrite(IN3, HIGH); 
    digitalWrite(IN4, LOW);

    analogWrite(ENA, velocidadmax);  
    analogWrite(ENB, velocidadmax);  
    tiempoInicioGiro = millis(); 
    girandoIzquierda = true; 
  } else {
   
    if (millis() - tiempoInicioGiro >= duracionGiro90) {
      detenerRobot(); 
      girandoIzquierda = false; 
    }
  }
}