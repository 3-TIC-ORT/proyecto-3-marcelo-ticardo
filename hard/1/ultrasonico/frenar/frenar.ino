//uAl  sensar una distancia menor o igual  a 75 cm que frenen los motores
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
unsigned long UltimaMedicion = 0;

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
}

void loop() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadmax); 
  analogWrite(ENB, velocidadmax);
  if(millis() - UltimaMedicion >= INTERVALO) {
    UltimaMedicion = millis();
    
   
    float distancia1 = medirDistancia(TRIG1, ECHO1);
    float distancia2 = medirDistancia(TRIG2, ECHO2);

    
    Serial.print("Distancia Sensor 1: ");
    Serial.print(distancia1);
    Serial.println(" cm");

    Serial.print("Distancia Sensor 2: ");
    Serial.print(distancia2);
    Serial.println(" cm");

   
    if (distancia1 <= DISTANCIA_MINIMA || distancia2 <= DISTANCIA_MINIMA) {
      Serial.println("Advertencia: Distancia demasiado corta. ¡Frenar!");
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
       analogWrite(ENA, velocidadmin); 
       analogWrite(ENB, velocidadmin);
      
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
