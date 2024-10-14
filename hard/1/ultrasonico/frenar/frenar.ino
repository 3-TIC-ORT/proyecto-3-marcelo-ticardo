#define TRIG1 7 
#define ECHO1 A1
#define TRIG2 8
#define ECHO2 A0   
#define INTERVALO 100  
#define SOUND_SPEED 0.034 
#define DISTANCIA_MINIMA 75
#define ENA 10  
#define ENB 11  
#define IN1 4   
#define IN2 5   
#define IN3 3   
#define IN4 2   

int velocidadmax = 255; 
int velocidadmin = 0;
unsigned long medicionAnterior = 0;
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
  Serial.begin(9600);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void loop() {
  analogWrite(ENA, velocidadmax); 
  analogWrite(ENB, velocidadmax);

  // Verificar la dirección del robot
  if (digitalRead(IN1) == HIGH && digitalRead(IN2) == LOW && digitalRead(IN3) == HIGH && digitalRead(IN4) == LOW) {
    direccion = true;  // Movimiento hacia adelante
  } else if (digitalRead(IN1) == LOW && digitalRead(IN2) == HIGH && digitalRead(IN3) == LOW && digitalRead(IN4) == HIGH) {
    direccion = false;  // Movimiento hacia atrás
  }

  if (millis() - UltimaMedicion >= INTERVALO) {
    UltimaMedicion = millis();
    
    float distancia;
    
    // Verificar la dirección del robot y medir la distancia con el sensor adecuado
    if (direccion == true) {
      distancia = medirDistancia(TRIG1, ECHO1);  // Sensor frontal
      Serial.print("Distancia Sensor Frontal: ");
    } else {
      distancia = medirDistancia(TRIG2, ECHO2);  // Sensor trasero
      Serial.print("Distancia Sensor Trasero: ");
    }
    
    Serial.print(distancia);
    Serial.println(" cm");

    // Si la distancia es menor que la mínima, detener el robot
    if (distancia <= DISTANCIA_MINIMA) {
      Serial.println("Advertencia: Distancia demasiado corta. ¡Frenar!");
      detenerRobot();
    }
  }
}

// Función para medir la distancia con el sensor ultrasónico
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

// Función para detener el robot
void detenerRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmin); 
  analogWrite(ENB, velocidadmin);
}
