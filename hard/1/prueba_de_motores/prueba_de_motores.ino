#define ENA 10  
#define ENB 11  
#define IN1 3   
#define IN2 4  
#define IN3 2  
#define IN4 5  

int velocidad = 255;   

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  Serial.begin(9600);  
}

void loop() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad); 
  analogWrite(ENB, velocidad);
  Serial.println("Moviendo hacia adelante");
  delay(5000);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  Serial.println("Moviendo hacia atras");
  delay(5000);
}
