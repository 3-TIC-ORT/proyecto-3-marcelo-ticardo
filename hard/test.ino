// Define los pines de los motores
const int motorPinA = 3;  // Motor A (dirección hacia adelante)
const int motorPinB = 4;  // Motor B (dirección hacia atrás)

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
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);

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
      digitalWrite(motorPinA, LOW);
      digitalWrite(motorPinB, LOW);
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
      digitalWrite(motorPinA, LOW);
      digitalWrite(motorPinB, LOW);
      running = false;
      Serial.println("obstáculo atrás");
    }
  } else {
    obstacleBack = false;
  }

  // Control de los motores
  if (running && !obstacleFront && !obstacleBack) {
    if (direction == "adelante") {
      digitalWrite(motorPinA, HIGH);
      digitalWrite(motorPinB, LOW);
    } else if (direction == "atras") {
      digitalWrite(motorPinA, LOW);
      digitalWrite(motorPinB, HIGH);
    }

    // Contar las marcas detectadas
    if (digitalRead(sensorIR1) == HIGH && digitalRead(sensorIR2) == HIGH &&
        digitalRead(sensorIR3) == LOW && digitalRead(sensorIR4) == LOW) {
      count++;
      delay(100); // Ajusta el tiempo según sea necesario
    }

    if (count >= targetCount) {
      // Detener los motores
      digitalWrite(motorPinA, LOW);
      digitalWrite(motorPinB, LOW);
      running = false;
      Serial.println("Llegué");
    }

    // Control de la línea
    if (digitalRead(sensorIR1) == LOW && digitalRead(sensorIR2) == LOW) {
      // Ajusta los motores para seguir la línea
      if (digitalRead(sensorIR3) == HIGH && digitalRead(sensorIR4) == HIGH) {
        // Mantenerse en la línea
        digitalWrite(motorPinA, HIGH);
        digitalWrite(motorPinB, LOW);
      } else if (digitalRead(sensorIR3) == LOW && digitalRead(sensorIR4) == HIGH) {
        // Ajustar si se sale de la línea
        digitalWrite(motorPinA, LOW);
        digitalWrite(motorPinB, HIGH);
      } else if (digitalRead(sensorIR3) == HIGH && digitalRead(sensorIR4) == LOW) {
        // Ajustar si se sale de la línea
        digitalWrite(motorPinA, HIGH);
        digitalWrite(motorPinB, LOW);
      }
    }
  }
}