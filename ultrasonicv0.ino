const int ENA = 22;
const int ENB = 17;

const int IN1 = 18;
const int IN2 = 19;
const int IN3 = 20;
const int IN4 = 21;
int spd = 255;
const int pingPin = 26; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 27; // Echo Pin of Ultrasonic Sensor

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(115200); // Starting Serial Terminal
}

void loop() {
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(100);

  if (cm > 10 && cm < 30)) {
    spd = 128;
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(IN1, HIGH); )
    digitalWrite(IN2, LOW); )
    digitalWrite(IN3, HIGH); )
    digitalWrite(IN4, LOW); )
    analogWrite(ENA, spd);
    analogWrite(ENB, spd);
  }
  else if (cm > 30)) {
    spd = 255;
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(IN1, HIGH); )
    digitalWrite(IN2, LOW); )
    digitalWrite(IN3, HIGH); )
    digitalWrite(IN4, LOW); )
    analogWrite(ENA, spd);
    analogWrite(ENB, spd);
  }
  else {
    spd = 0;
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(IN1, LOW); )
    digitalWrite(IN2, LOW); )
    digitalWrite(IN3, LOW); )
    digitalWrite(IN4, LOW); )
    analogWrite(ENA, spd);
    analogWrite(ENB, spd);

  }


}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}