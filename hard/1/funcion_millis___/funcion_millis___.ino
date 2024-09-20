long ultimosMillis = 0;
const long intervalos = 500;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
 
}


void loop() {
  long titilo = millis();

if(titilo - ultimosMillis >= intervalos){
   ultimosMillis = titilo;

 if(digitalRead(LED_BUILTIN)== LOW){
  digitalWrite(LED_BUILTIN,HIGH);
  } else {
    digitalWrite(LED_BUILTIN,LOW);
    }
  }
}
