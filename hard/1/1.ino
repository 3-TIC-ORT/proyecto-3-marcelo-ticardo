#define ENA 10  
#define ENB 11  
#define IN1 3   
#define IN2 4  
#define IN3 2  
#define IN4 5  
#define TRIG1 7 
#define ECHO1 A1
#define TRIG2 8
#define ECHO2 A0   
#define INTERVALO 100  
#define SOUND_SPEED 0.034 
#define DISTANCIA_MINIMA 75
#define IR1 A2
#define IR2 A3
#define IR3 A4
#define IR4 A5
int velocidad = 255; // Velocidad máxima
int velocidadmin = 0;
unsigned long medicionAnterior = 0;
const long intervalo = 200;
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
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  Serial.begin(9600);
  pinMode(IN1, LOW);
  pinMode(IN2, LOW);
  pinMode(IN3, LOW);
  pinMode(IN4, LOW);  
  analogWrite(ENA, velocidadmin); 
  analogWrite(ENB, velocidadmin); 
}


void loop(){
  }
