#define ENA 10  
#define ENB 11  
#define IN1 3   
#define IN2 4  
#define IN3 2   
#define IN4 5   
#define IR1 A2 // gris
#define IR4 A5 // negro
#define IR2 A3 // negro
#define IR3 A4 // gris

int velocidadmax = 255;
int velocidadCorreccion = 10;
int velocidadmed = 125;
int velocidadmin = 0;
bool direcccion;

void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);

  Serial.begin(9600);
  }

void loop(){

  // Escuchar comandos desde el puerto serie
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command == "ADELANTE") {
      moverAdelante();
    } else if (command == "ATRAS") {
      moverAtras();
    } else if (command == "PARAR"){
      detenerRobot();
      }
  }

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
  analogWrite(ENA, velocidadmed);
  analogWrite(ENB, velocidadmed);
}

void moverAtras() {
  direccion = false;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidadmed);
  analogWrite(ENB, velocidadmed);
}

void correccionIzquierda() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadCorreccion);
  analogWrite(ENB, velocidadmed);
}

void correccionDerecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmed);
  analogWrite(ENB, velocidadCorreccion);
}
