// No se, lo hice con chatgpt
String inputString = "";         // Cadena para guardar la entrada serial
bool stringComplete = false;     // Si la cadena está completa

void setup() {
  // Inicializa la comunicación serial
  Serial.begin(9600);
  inputString.reserve(200);
}

void loop() {
  // Cuando la cadena esté completa
  if (stringComplete) {
    Serial.println("Procesando instrucción...");

    // Procesa la cadena recibida
    if (inputString.indexOf("adelante") >= 0) {
      moverAdelante();
    } else if (inputString.indexOf("atras") >= 0) {
      moverAtras();
    }
    
    // Limpia la cadena para la próxima entrada
    inputString = "";
    stringComplete = false;
  }
}

// Función que se ejecuta cuando se recibe un carácter por el puerto serial
void serialEvent() {
  while (Serial.available()) {
    // Obtiene el nuevo byte:
    char inChar = (char)Serial.read(); 
    // Añade al final de la cadena:
    inputString += inChar;
    // Si la cadena está completa:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void moverAdelante() {
  Serial.println("Moviendo hacia adelante");
  // Aquí el código para mover el robot hacia adelante
}

void moverAtras() {
  Serial.println("Moviendo hacia atrás");
  // Aquí el código para mover el robot hacia atrás
}