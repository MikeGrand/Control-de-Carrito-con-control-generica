#include <Bluepad32.h>

const int ENA = 14;
const int IN1 = 27;
const int IN2 = 26;

const int ENB = 25;
const int IN3 = 33;
const int IN4 = 32;

const int pwmFreq = 20000;
const int pwmRes = 8;
const int pwmChannelA = 0; 
const int pwmChannelB = 1; 

GamepadPtr myGamepad;

void onConnectedGamepad(GamepadPtr gp) {
  Serial.println("Control conectado!");
  myGamepad = gp;
}

void onDisconnectedGamepad(GamepadPtr gp) {
  Serial.println("Control desconectado!");
  myGamepad = nullptr;
}

void setup() {
  Serial.begin(115200);
  BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);

  // Motor principal
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  ledcSetup(pwmChannelA, pwmFreq, pwmRes);
  ledcAttachPin(ENA, pwmChannelA);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  ledcWrite(pwmChannelA, 0);

  // Motor volante
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  ledcSetup(pwmChannelB, pwmFreq, pwmRes);
  ledcAttachPin(ENB, pwmChannelB);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(pwmChannelB, 0);
}

void moverAdelante(int vel) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(pwmChannelA, vel);
}

void moverAtras(int vel) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(pwmChannelA, vel);
}

void pararMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  ledcWrite(pwmChannelA, 0);
}

void girarDerecha(int vel) {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(pwmChannelB, vel);
}

void girarIzquierda(int vel) {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  ledcWrite(pwmChannelB, vel);
}

void pararVolante() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(pwmChannelB, 0);
}

void loop() {
  BP32.update();

  if (myGamepad && myGamepad->isConnected()) {
    int ly = myGamepad->axisY();

    if (ly < -50) { // Adelante
      int vel = map(ly, -512, -50, 255, 255); // Máximo PWM siempre
      moverAdelante(vel);
      Serial.println("Adelante");
    } 
    else if (ly > 50) { // Atrás
      int vel = map(ly, 50, 512, 255, 255); // Máximo PWM siempre
      moverAtras(vel);
      Serial.println("Atrás");
    } 
    else {
      pararMotor();
      Serial.println("Parado");
    }

    //Volante (joystick derecho eje X)
    int rx = myGamepad->axisRX();

    if (rx > 50) { // Derecha
      int vel = map(rx, 50, 512, 255, 255); 
      girarDerecha(vel);
      Serial.println("Volante derecha");
    } 
    else if (rx < -50) { 
      int vel = map(rx, -512, -50, 255, 255); 
      girarIzquierda(vel);
      Serial.println("Volante izquierda");
    } 
    else {
      pararVolante();
      Serial.println("Volante centrado");
    }

  } else {
    pararMotor();
    pararVolante();
  }

  delay(20);
}
