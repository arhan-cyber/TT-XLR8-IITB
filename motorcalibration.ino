#include <Servo.h>
#include <string.h>

// Pin assignments for motor control
const int servoPin = 14;
const int ENA = 22;
const int ENB = 17;
const int IN1 = 21;
const int IN2 = 20;
const int IN3 = 19;
const int IN4 = 18;
const int pingPin = 27; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 26;

int spd = 255;
int cmd = 0; 
const int calibratedTime = 1500;
int angle;
int direction;
int x = 1;


void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void turn() {
  if (direction == 1) {
    cmd = 3;
  }
  else if (direction == 2) {
    cmd = 4;
  }
  updateMotorControl();
  applyMotorControl();
  delay(calibratedTime*angle/360);
  cmd = 0;
  direction = 0;
  updateMotorControl();
  applyMotorControl();
}

void updateMotorControl() {
  // Display motor control information
  Serial.print("cmd: ");
  Serial.print(cmd);   // Display motor command
  Serial.print(", speed: ");
  Serial.println(spd); // Display motor speed
}

void applyMotorControl() {
  switch (cmd) {
    case 1:  // Forward
      digitalWrite(IN1, HIGH); 
      digitalWrite(IN2, LOW); 
      digitalWrite(IN3, HIGH); 
      digitalWrite(IN4, LOW); 
      break;
    case 2:  // Backward
      digitalWrite(IN1, LOW); 
      digitalWrite(IN2, HIGH); 
      digitalWrite(IN3, LOW); 
      digitalWrite(IN4, HIGH); 
      break;
    case 3:  // Right
      digitalWrite(IN1, HIGH); 
      digitalWrite(IN2, LOW); 
      digitalWrite(IN3, LOW); 
      digitalWrite(IN4, HIGH); 
      break;
    case 4:  // Left
      digitalWrite(IN1, LOW); 
      digitalWrite(IN2, HIGH); 
      digitalWrite(IN3, HIGH); 
      digitalWrite(IN4, LOW); 
      break;
    default:  // Stop
      digitalWrite(IN1, LOW); 
      digitalWrite(IN2, LOW); 
      digitalWrite(IN3, LOW); 
      digitalWrite(IN4, LOW); 
      spd = 0;
      break;
  }
  // Apply the calculated motor speed to both motors
  analogWrite(ENA, spd);
  analogWrite(ENB, spd);
}

void loop() {
  if (x ==1) {
    direction = 1;
    angle = 180;
    turn();
    x= 0;
  }


}
