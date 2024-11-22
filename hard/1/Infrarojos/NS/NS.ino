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

}

void loop() {
  int valorIR1 = analogRead(IR1);  
  int valorIR2 = analogRead(IR2);  
  int valorIR3 = analogRead(IR3);  
  int valorIR4 = analogRead(IR4);  
  if(IR1 <100 && IR3 < 100 && IR2 > 800 && IR4 > 800){
      moverAadelante();
  } else if ( IR1 > 100 && IR3 >100){
    detenerRobot(); 
  }else if (IR2 <

}
void moverAdelante(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN1, velocidadmax);
  analogWrite(EN2, velocidadmax);
  }

void detenerRobot(){
    digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN1, velocidadmin);
  analogWrite(EN2, velocidadmin);
}
}
