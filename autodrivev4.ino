#include <Servo.h> 

// Pin assignments for motor control
const int servoPin = 14;
const int ENA = 22;
const int ENB = 17;
const int IN1 = 21;
const int IN2 = 20;
const int IN3 = 19;
const int IN4 = 18;
const int pingPin = 27; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 26; // Echo Pin of Ultrasonic Sensor
const int calibratedTime = 1500;
const int calibratedSpeed = 109; // cm / sec // 109 changed to 130 for 
long duration;
int cm = 0;
int cmd = 0;
int spd = 0;
bool bot_cannot_continue = false;
int stoppingDistance = 10;
const int numAngles = 5;    // Number of angle increments (0, 45, 90, 135, 180)
int angles[numAngles] = {0, 45, 90, 135, 180}; // Angle increments
int distances[numAngles];   // Array to store distance values
int maxIndex = 0;        // Index of the angle with the minimum distance
int maxDistance = 0; // Initialize minimum distance to a high value


// Create a servo object
Servo uServo;

void setup() {
  // Start Serial for debugging
  Serial.begin(115200);
  // Configure motor control pins as outputs
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);

  uServo.attach(servoPin, 400, 2600); // Minimum and maximum pulse width (in µs) to go from 0° to 180°.
  Serial.begin(115200); // Starting Serial Terminal
/*   uServo.write(90); // look in front
 */}

void applyMotorControl(int cmd, int spd) {
  // Display motor control information
  Serial.print("cmd: ");
  Serial.print(cmd);   // Display motor command
  Serial.print(", speed: ");
  Serial.println(spd); // Display motor speed
  switch (cmd) {
    case 2:  // backward
      digitalWrite(IN1, HIGH); 
      digitalWrite(IN2, LOW); 
      digitalWrite(IN3, HIGH); 
      digitalWrite(IN4, LOW); 
      break;
    case 1:  // Forward
      digitalWrite(IN1, LOW); 
      digitalWrite(IN2, HIGH); 
      digitalWrite(IN3, LOW); 
      digitalWrite(IN4, HIGH); 
      break;
    case 4:  // left
      digitalWrite(IN1, HIGH); 
      digitalWrite(IN2, LOW); 
      digitalWrite(IN3, LOW); 
      digitalWrite(IN4, HIGH); 
      break;
    case 3:  // right
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


int ping() {
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  return microsecondsToCentimeters(duration);
}


void turnCar(int angle) {
  if (angle > 90) { 
    cmd = 3; //  clockwise
  }
  else if (angle < 90) { //anti-clockwise
    cmd = 4;
  }
  else if (angle == 90) { //anti-clockwise
    cmd = 1;
  }
  applyMotorControl(cmd, 255);
  delay(calibratedTime*angle/360);
  applyMotorControl(0, 0);
}


long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void loop() {
// Rotate the servo and measure distances
  for (int i = 0; i < numAngles; i++) {
    uServo.write(angles[i]); // Set servo to the current angle
    // Wait for the servo to reach the position

    // Send a ping and get the distance
    delay(200); // Wait for the sensor to settle
    distances[i] = ping(); // Get distance in cm

    // Print angle and distance
    Serial.print("Angle: ");
    Serial.print(angles[i]);
    Serial.print("° Distance: ");
    Serial.print(distances[i]);
    Serial.println(" cm");
  }   
  int maxIndex = 0; 
  for (int i = 1; i < numAngles; i++) {
      if (arr[i] > arr[maxIndex]) {
          maxIndex = i;
      }
  }
  maxDistance = distances[maxIndex];
  reqAngle = angles[maxIndex];
  // Print the required angle with the maximum distance
  Serial.print("Angle with maximum distance: ");
  Serial.print(reqAngle);
  Serial.print("° Distance: ");
  Serial.println(maxDistance);
  
  // turn car to required angle
  turnCar(reqAngle); 
  if ((maxDistance > stoppingDistance) && (maxDistance <30)) { // slowly reach object
    digitalWrite(LED_BUILTIN, LOW);
    applyMotorControl(1, 128);
    digitalWrite(LED_BUILTIN, HIGH);
    delay((cm-15)/calibratedSpeed*1000*2); // double the delay as half the speed
    applyMotorControl(0, 0); 
  }
  else if (maxDistance > 30) { // full speed go forward
    digitalWrite(LED_BUILTIN, LOW);
    applyMotorControl(1, 255);
    digitalWrite(LED_BUILTIN, HIGH);
    delay((cm-25)/calibratedSpeed*1000);
    applyMotorControl(0, 0); 
  }
  else { // unable to manuver
    digitalWrite(LED_BUILTIN, LOW);
    applyMotorControl(2, 128);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    applyMotorControl(0, 0);
  }
digitalWrite(LED_BUILTIN, LOW);
};
