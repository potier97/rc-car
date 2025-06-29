#include <YK04_Module.h>

// === Pins ===
const int PIN_BTN_A = 2;
const int PIN_BTN_B = 3;
const int PIN_BTN_C = 4;
const int PIN_BTN_D = 5;

// === Motor driver pins (L298N) ===
const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 8;
const int IN4 = 9; 
const int ENA = 10;
const int ENB = 11;

// === Speed control ===
const int SPEED_LOW  = 150;
const int SPEED_HIGH = 255;
int currentSpeed = SPEED_LOW;

// === YK04 controller ===
YK04_Module* remote;

void setup() {
  // Initialize motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  remote = new YK04_Module(PIN_BTN_A, PIN_BTN_B, PIN_BTN_C, PIN_BTN_D);
}

void loop() {
  YK04_Module::Button btn = remote->multipleRead();
  Serial.println(btn);  
  switch (btn) {
    case YK04_Module::Button::A:
      moveForward();
      break;
    case YK04_Module::Button::B:
      moveBackward();
      break;
    case YK04_Module::Button::C:
      turnLeft();
      break;
    case YK04_Module::Button::D:
      turnRight();
      break;
    case YK04_Module::Button::NOT:
      stopMotors();
      break;
  }

  if (btn == YK04_Module::Button::A && remote->isB()) {
    toggleSpeed();
    delay(300);
  } else if (btn == YK04_Module::Button::C && remote->isD()) {
    toggleSpeed();
    delay(300);
  }
}

// === Motion functions ===

void moveForward() {
  setMotorDirection(HIGH, LOW, HIGH, LOW);
  setMotorSpeed(currentSpeed, currentSpeed);
}

void moveBackward() {
  setMotorDirection(LOW, HIGH, LOW, HIGH);
  setMotorSpeed(currentSpeed, currentSpeed);
}

void turnLeft() {
  setMotorDirection(LOW, HIGH, HIGH, LOW);
  setMotorSpeed(currentSpeed, currentSpeed);
}

void turnRight() {
  setMotorDirection(HIGH, LOW, LOW, HIGH);
  setMotorSpeed(currentSpeed, currentSpeed);
}

void stopMotors() {
  setMotorDirection(LOW, LOW, LOW, LOW);
  setMotorSpeed(0, 0);
}

void toggleSpeed() {
  currentSpeed = (currentSpeed == SPEED_LOW) ? SPEED_HIGH : SPEED_LOW;
}

// === Helper functions ===

void setMotorDirection(bool in1, bool in2, bool in3, bool in4) {
  digitalWrite(IN1, in1);
  digitalWrite(IN2, in2);
  digitalWrite(IN3, in3);
  digitalWrite(IN4, in4);
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);
}
