#define EN1 10  
#define EN2 11  
#define IN1 3   
#define IN2 4  
#define IN3 2   
#define IN4 5   
#define IR1 A2 
#define IR2 A3 
#define IR3 A4 
#define IR4 A5

unsigned long tiempoAnterior = 0;
unsigned long tiempoRetroceso = 0;
unsigned long tiempoAvance = 0;

const long intervalo = 200;
int velocidadmax = 255;
int velocidadCorreccion = 177;
int velocidadmin = 0;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;
  }

  int valorIR1 = analogRead(IR1);  
  int valorIR2 = analogRead(IR2);  
  int valorIR3 = analogRead(IR3);  
  int valorIR4 = analogRead(IR4);  

  // Caso 1: IR1 e IR3 > 500
  if (valorIR1 > 500 && valorIR3 > 500) {
    detenerMotor(EN2);
    retrocederMotor1();

    while (analogRead(IR1) > 100 || analogRead(IR3) > 100) {
      delay(10); 
    }

    tiempoRetroceso = millis() - tiempoAnterior;
    tiempoAvance = tiempoRetroceso / 2;
    
    avanzarMotor1(tiempoAvance);
  }

  // Caso 2: IR2 e IR4 < 100
  else if (valorIR2 < 100 && valorIR4 < 100) {
    detenerMotor(EN1);
    retrocederMotor2();


    while (analogRead(IR2) < 500 || analogRead(IR4) < 500) {
      delay(10); 
    }


    tiempoRetroceso = millis() - tiempoAnterior;
    tiempoAvance = tiempoRetroceso / 2;

    avanzarMotor2(tiempoAvance);
  } else {
    moverAdelante();
  }
}

void detenerRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN1, velocidadmin);
  analogWrite(EN2, velocidadmin);
}

void detenerMotor(int motor) {
  analogWrite(motor, velocidadmin);
}

void retrocederMotor1() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN1, velocidadmax);
}

void retrocederMotor2() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(EN2, velocidadmax);
}

void avanzarMotor1(unsigned long tiempo) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(EN1, velocidadmax);
  delay(tiempo);
  detenerMotor(EN1);
}

void avanzarMotor2(unsigned long tiempo) {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN2, velocidadmax);
  delay(tiempo);
  detenerMotor(EN2);
}

void moverAdelante() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN1, velocidadmax);
  analogWrite(EN2, velocidadmax);
}
