#define EN1 10  //mot izq
#define EN2 11  //mot der
#define IN1 3  //mot izq 
#define IN2 4  //mot izq
#define IN3 2  //mot der
#define IN4 5  //mot der
#define IR1 A2 //der
#define IR2 A3 //izq
#define IR3 A4 //der
#define IR4 A5 //izq

unsigned long tiempoAnterior = 0;
unsigned long tiempoRetroceso = 0;
unsigned long tiempoAvance = 0;

const long intervalo = 200;
//int velocidadmax = 255;
//int velocidadCorreccion = 177;
int velocidadmax = 177;
int velocidadCorreccion = 150;
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

//  Serial.print("IR1: "); Serial.println(valorIR1); //der
//  Serial.print("IR2: "); Serial.println(valorIR2); //izq
//  Serial.print("IR3: "); Serial.println(valorIR3); //der
//  Serial.print("IR4: "); Serial.println(valorIR4); //izq

  // Caso 1: IR1 e IR3 > 800
  if (valorIR1 > 800 && valorIR3 > 800) { //Si mis sensores de la der no ven blanco
  detenerMotor(EN2);
  detenerMotor(EN1);
  retrocederMotor2(velocidadCorreccion); //Enciendo el motor izq para atras
  
  // Actualiza tiempoAnterior antes del while
  tiempoAnterior = millis();

  while (analogRead(IR1) > 100 || analogRead(IR3) > 100) {
    delay(10); // Espera hasta que ambos sensores detecten valores < 100
    valorIR1 = analogRead(IR1);  
    valorIR3 = analogRead(IR3); 
    Serial.println("corrigiendo no veo blanco");
    Serial.print("IR1: "); Serial.println(valorIR1); //der
    Serial.print("IR2: "); Serial.println(valorIR2); //izq
    Serial.print("IR3: "); Serial.println(valorIR3); //der
    Serial.print("IR4: "); Serial.println(valorIR4); //izq}
    if(millis() - tiempoAnterior > 2500){
      retrocederMotor1(velocidadCorreccion);
      delay(1000);
      break;
    }
  }
  Serial.print("corrigiendo motor otro, tiempo retoceso ");
  detenerMotor(EN2);
  detenerMotor(EN1);
  tiempoRetroceso = millis() - tiempoAnterior;
  if (valorIR2 < 100 && valorIR4 < 100)
    Serial.println("Sigue descal");

}
  // Caso 2: IR2 e IR4 < 100
  else if (valorIR2 < 100 && valorIR4 < 100) {
    detenerMotor(EN1);
    detenerMotor(EN2);
    retrocederMotor1(velocidadCorreccion);
    
  // Actualiza tiempoAnterior antes del while
  tiempoAnterior = millis();
    Serial.println("corrigiendo no veo NEGRO");
    while (analogRead(IR2) < 800 || analogRead(IR4) < 800) {
      delay(10); // Espera hasta que ambos sensores detecten valores > 800
      valorIR1 = analogRead(IR1);  
      valorIR3 = analogRead(IR3); 
      Serial.println("corrigiendo no veo blanco");
      Serial.print("IR1: "); Serial.println(valorIR1); //der
      Serial.print("IR2: "); Serial.println(valorIR2); //izq
      Serial.print("IR3: "); Serial.println(valorIR3); //der
      Serial.print("IR4: "); Serial.println(valorIR4); //izq
      if(millis() - tiempoAnterior > 2500){
      retrocederMotor2(velocidadCorreccion);
      delay(1000);
      break;
    }
    }
    detenerMotor(EN1);
    detenerMotor(EN2);
  }
  // Movimiento por defecto: avanzar
  else {
    moverAdelante();
  }
}

void detenerMotor(int motor) {
  analogWrite(motor, velocidadmin);
}

void retrocederMotor1(int velocidad) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN1, velocidad);
}

void retrocederMotor2(int velocidad) {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(EN2, velocidad);
}

void avanzarMotor1(unsigned long tiempo, int velocidad) { //motor izquierda
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(EN1, velocidad);
  delay(tiempo);
  detenerMotor(EN1);
}

void avanzarMotor2(unsigned long tiempo, int velocidad) { //motor derecha
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN2, velocidad);
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
