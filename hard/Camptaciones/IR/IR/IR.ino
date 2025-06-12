// Motores y Puente H
#define ENA 10  
#define ENB 11  
#define IN1 3   // motor izquierdo
#define IN2 4
#define IN3 2   // motor derecho
#define IN4 5

// Infrarrojos
#define IR1 A2 // sensor derecha delantera
#define IR2 A3 // sensor izquierda delantera
#define IR3 A4 // sensor derecha trasera
#define IR4 A5 // sensor izquierda trasera

int velocidadIzquierda = 255;
int velocidadDerecha = 65;
int velocidadCorreccion = 90;
int velocidadMinima = 0;


class PID {
  public:
    PID(float kp, float ki, float kd, float initialIntegral = 0.0, float outputMin = -1.0, float outputMax = 1.0) {
      Kp = kp;
      Ki = ki;
      Kd = kd;
      integral = initialIntegral;
      previousError = 0;
      minOutput = outputMin;
      maxOutput = outputMax;
    }

    void setSetpoint(float sp) {
      setpoint = sp;
    }

    void setOutputLimits(float minOut, float maxOut) {
      minOutput = minOut;
      maxOutput = maxOut;
    }

    void resetIntegral(float newIntegral = 0.0) {
      integral = newIntegral;
    }

    float compute(float measurement) {
      float error = setpoint - measurement;
      integral += error;
      float derivative = error - previousError;
      previousError = error;

      float output = Kp * error + Ki * integral + Kd * derivative;
      output = constrain(output, minOutput, maxOutput);
      return output;
    }

  private:
    float Kp, Ki, Kd;
    float integral;
    float previousError;
    float setpoint = 0;
    float minOutput, maxOutput;
};

// PID object (you had a trailing comma error!)
PID pid(0.5, 0.1, 0.1, 0.0, -1.0, 1.0);

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IR1, INPUT); pinMode(IR2, INPUT);
  pinMode(IR3, INPUT); pinMode(IR4, INPUT);

  Serial.begin(9600);
  detenerRobot();
}

void loop() {
  follow_line();
}

int get_error(int cutoff) {
  int raw[4] = {
    analogRead(IR1),
    analogRead(IR3),
    analogRead(IR2),
    analogRead(IR4)
  };
  Serial.print(raw[0]);
  Serial.print(","); Serial.print(raw[1]);
  Serial.print(","); Serial.print(raw[2]);
  Serial.print(","); Serial.print(raw[3]);

  int error = 0;
  for (int i = 0; i < 4; i++) {
    if (raw[i] > cutoff) {
      if (i < 2) {
        error++;
      } else {
        error--;
      }
    }
  }
  return error;
}

void follow_line() {
  int err = get_error(500);
  float adj = pid.compute(err);  // You were missing a semicolon

  // Drive motors forward with speed adjustment
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);

  int leftSpeed = velocidadIzquierda;
  int rightSpeed = velocidadDerecha;

  // Adjust motor speeds based on PID output
  leftSpeed = constrain(leftSpeed + (adj * velocidadCorreccion), 0, 255);
  rightSpeed = constrain(rightSpeed - (adj * velocidadCorreccion), 0, 255);

  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);

  Serial.print(",");Serial.print(adj);
  Serial.print(","); Serial.println(err);
}

void detenerRobot() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidadMinima);
  analogWrite(ENB, velocidadMinima);
}
