#include <Servo.h> 
const int servoPin = 14;
const int ENA = 22;
const int ENB = 17;
const int IN1 = 18;
const int IN2 = 19;
const int IN3 = 20;
const int IN4 = 21;
int spd = 255;
int cmd = 0; 
long duration, inches, cm;
const int pingPin = 26; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 27; // Echo Pin of Ultrasonic Sensor

// Create a servo object
Servo uServo;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  uServo.attach(servoPin, 400, 2600); // Minimum and maximum pulse width (in µs) to go from 0° to 180°.
  Serial.begin(115200); // Starting Serial Terminal
  uServo.write(0);
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
  ping();
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if (cm > 10 && cm < 30) {
    spd = 128;
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (cm > 30) {
    spd = 255;
    digitalWrite(LED_BUILTIN, LOW);
  }
  else {
    spd = 0;
    digitalWrite(LED_BUILTIN, HIGH);
  }

/* // Rotation from 0 to 180°.
  for (int Angle = 0; Angle <= 180; Angle += 1) {
    uServo.write(Angle);
    delay(5);
  }

// Rotation from 180° to 0.
  for (int Angle = 180; Angle >= 0; Angle -= 1) {
    uServo.write(Angle);
    delay(5);
  } */

}

void ping() {
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}