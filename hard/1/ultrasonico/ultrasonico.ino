//Al sensar un objeto dice por puesto serie la dsitancia a la que  esta.
#define TRIG_PIN 6    
#define ECHO_PIN 9    
#define INTERVAL 100  
#define SOUND_SPEED 0.034  

unsigned long lastMeasureTime = 0; 


void setup() {
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 
 
  Serial.begin(9600);
}


void loop() {
  
  if (millis() - lastMeasureTime >= INTERVAL) {
  
  lastMeasureTime = millis();

  float distance = medirDistancia();
    
 
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
  }
}


float medirDistancia() {
  // Enviar un pulso de 10 microsegundos en el pin TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  
  long duration = pulseIn(ECHO_PIN, HIGH);
 
  
  float distance = duration * SOUND_SPEED / 2;

  return distance;
}
