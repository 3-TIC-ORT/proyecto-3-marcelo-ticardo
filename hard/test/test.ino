// Código hecho con ChatGPT a modo de base para tener en cuenta cuando se haga el código verdadero
// Definición de pines del puente H
#define IN1 3
#define IN2 4
#define IN3 2
#define IN4 5
#define ENA 11
#define ENB 12

// Define los pines de los sensores IR
const int sensorIR1 = A0; // Sensor 1 - Izquierda, blanco
const int sensorIR2 = A1; // Sensor 2 - Izquierda, blanco
const int sensorIR3 = A2; // Sensor 3 - Derecha, negro
const int sensorIR4 = A3; // Sensor 4 - Derecha, negro

// Define los pines de los sensores ultrasónicos
const int trigPinFront = 7;  // Trig del sensor ultrasónico frontal
const int echoPinFront = 8;  // Echo del sensor ultrasónico frontal
const int trigPinBack = 9;   // Trig del sensor ultrasónico trasero
const int echoPinBack = 10;  // Echo del sensor ultrasónico trasero

int count = 0;
int targetCount = 0;
bool running = false;
bool obstacleFront = false;
bool obstacleBack = false;
String direction = "";

void setup() {
  Serial.begin(9600);

  // Configura los pines de los motores como salidas
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Configura los pines de los sensores IR como entradas
  pinMode(sensorIR1, INPUT);
  pinMode(sensorIR2, INPUT);
  pinMode(sensorIR3, INPUT);
  pinMode(sensorIR4, INPUT);

  // Configura los pines de los sensores ultrasónicos
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(trigPinBack, OUTPUT);
  pinMode(echoPinBack, INPUT);

  digitalWrite(trigPinFront, LOW);
  digitalWrite(trigPinBack, LOW);
}

void loop() {
  // Leer datos desde el puerto serie
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    if (input == "adelante" || input == "atras") {
      direction = input;
      running = true;
      obstacleFront = false;
      obstacleBack = false;
    } else {
      targetCount = input.toInt();
      count = 0; // Reinicia el contador
    }
  }

  // Detectar obstáculos con los sensores ultrasónicos
  long durationFront, distanceFront;
  long durationBack, distanceBack;

  digitalWrite(trigPinFront, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFront, LOW);
  durationFront = pulseIn(echoPinFront, HIGH);
  distanceFront = (durationFront / 2) / 29.1; // Convertir a cm

  digitalWrite(trigPinBack, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinBack, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinBack, LOW);
  durationBack = pulseIn(echoPinBack, HIGH);
  distanceBack = (durationBack / 2) / 29.1; // Convertir a cm

  // Si hay un obstáculo adelante, detener los motores
  if (distanceFront < 20) { // Ajusta el umbral según sea necesario
    obstacleFront = true;
    if (running) {
      stopMotors();
      running = false;
      Serial.println("obstáculo adelante");
    }
  } else {
    obstacleFront = false;
  }

  // Si hay un obstáculo atrás, detener los motores
  if (distanceBack < 20) { // Ajusta el umbral según sea necesario
    obstacleBack = true;
    if (running && direction == "atras") {
      stopMotors();
      running = false;
      Serial.println("obstáculo atrás");
    }
  } else {
    obstacleBack = false;
  }

  // Control de los motores
  if (running && !obstacleFront && !obstacleBack) {
    if (direction == "adelante") {
      moveForward();
    } else if (direction == "atras") {
      moveBackward();
    }

    // Contar las marcas detectadas
    if (digitalRead(sensorIR1) == HIGH && digitalRead(sensorIR2) == HIGH &&
        digitalRead(sensorIR3) == LOW && digitalRead(sensorIR4) == LOW) {
      count++;
      delay(100); // Ajusta el tiempo según sea necesario
    }

    if (count >= targetCount) {
      // Detener los motores
      stopMotors();
      running = false;
      Serial.println("Llegué");
    }

    // Control de la línea
    if (digitalRead(sensorIR1) == LOW && digitalRead(sensorIR2) == LOW) {
      // Ajusta los motores para seguir la línea
      if (digitalRead(sensorIR3) == HIGH && digitalRead(sensorIR4) == HIGH) {
        // Mantenerse en la línea
        moveForward();
      } else if (digitalRead(sensorIR3) == LOW && digitalRead(sensorIR4) == HIGH) {
        // Ajustar si se sale de la línea
        moveBackward();
      } else if (digitalRead(sensorIR3) == HIGH && digitalRead(sensorIR4) == LOW) {
        // Ajustar si se sale de la línea
        moveForward();
      }
    }
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255); // Velocidad máxima
  analogWrite(ENB, 255); // Velocidad máxima
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255); // Velocidad máxima
  analogWrite(ENB, 255); // Velocidad máxima
}

void stopMotors() {
  analogWrite(ENA, 0); // Apaga los motores
  analogWrite(ENB, 0); // Apaga los motores
}
