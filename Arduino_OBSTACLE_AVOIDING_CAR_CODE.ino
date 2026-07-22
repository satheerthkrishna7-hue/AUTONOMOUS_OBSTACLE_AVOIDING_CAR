#include <Servo.h>
#include <SoftwareSerial.h>

// MOTOR DRIVER PINS
const int motordriveIN1 = 2;
const int motordriveIN2 = 6;
const int motordriveIN3 = 7;
const int motordriveIN4 = 8;
const int motordriveENA = 9;
const int motordriveENB = 10;

// SERVO
Servo scanservo;
const int servopin = 3;

// ULTRASONIC SENSOR
const int trigPin = 11;
const int echoPin = 12;

// BLUETOOTH CONNECTION TX = A0, RX =	A1
SoftwareSerial bluetooth(A0,A1);
bool automode = false;

// SETTINGS
const int obstacleDistance = 35;   // cm
const int reverseTime = 300;       // reduced, so it will not move back too much
const int turnTime = 750;          // tune this for around 90 degree turn

void setup() {

  bluetooth.begin(9600);

  pinMode(motordriveIN1, OUTPUT);
  pinMode(motordriveIN2, OUTPUT);
  pinMode(motordriveIN3, OUTPUT);
  pinMode(motordriveIN4, OUTPUT);
  pinMode(motordriveENA, OUTPUT);
  pinMode(motordriveENB, OUTPUT);

  scanservo.attach(servopin);
  servocenter();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  if (bluetooth.available())
    {
        char cmd = bluetooth.read();

        switch(cmd){
          
          case 'A':
             stopcar();
             automode = true;
             break;

          case 'M':
             automode = false;
             stopcar();
             break;

          case 'F':
            if(!automode){
             moveforward();}
             break;
          
          case 'B':
            if(!automode){
             movebackward();}
             break;

          case 'L':
            if(!automode){
             turnleft();}
             break;

          case 'R':
            if(!automode){
             turnright();}
             break;

          case 'S':
            if(!automode){
             stopcar();}
             break;
            }}
  if(automode){
    auto_code();}
}
  
  void auto_code()
  {
    float distance = measureDistance();

  Serial.print("Front: ");
  Serial.println(distance);

  if (distance > obstacleDistance) {
    moveforward();
    } 
  else {
    stopcar();
    delay(300);

    movebackward();
    delay(reverseTime);
    stopcar();
    delay(300);

    servoleft();
    float leftdistance = measureDistance();
    Serial.print("Left: ");
    Serial.println(leftdistance);

    servoright();
    float rightdistance = measureDistance();
    Serial.print("Right: ");
    Serial.println(rightdistance);

    servocenter();

    if (leftdistance > rightdistance) {
      turnleft();
      delay(turnTime);
    } else {
      turnright();
      delay(turnTime);
    }

    stopcar();
    delay(300);
  }
  }


void enableMotors() {
  digitalWrite(motordriveENA, HIGH);
  digitalWrite(motordriveENB, HIGH);
}

void moveforward() {
  enableMotors();

  // LEFT SIDE FORWARD
  digitalWrite(motordriveIN1, HIGH);
  digitalWrite(motordriveIN2, LOW);

  // RIGHT SIDE FORWARD
  digitalWrite(motordriveIN3, HIGH);
  digitalWrite(motordriveIN4, LOW);
}

void movebackward() {
  enableMotors();

  // LEFT SIDE BACKWARD
  digitalWrite(motordriveIN1, LOW);
  digitalWrite(motordriveIN2, HIGH);

  // RIGHT SIDE BACKWARD
  digitalWrite(motordriveIN3, LOW);
  digitalWrite(motordriveIN4, HIGH);
}

void turnleft() {
  enableMotors();

  // LEFT SIDE BACKWARD
  digitalWrite(motordriveIN1, LOW);
  digitalWrite(motordriveIN2, HIGH);

  // RIGHT SIDE FORWARD
  digitalWrite(motordriveIN3, HIGH);
  digitalWrite(motordriveIN4, LOW);
}

void turnright() {
  enableMotors();

  // LEFT SIDE FORWARD
  digitalWrite(motordriveIN1, HIGH);
  digitalWrite(motordriveIN2, LOW);

  // RIGHT SIDE BACKWARD
  digitalWrite(motordriveIN3, LOW);
  digitalWrite(motordriveIN4, HIGH);
}

void stopcar() {
  digitalWrite(motordriveENA, LOW);
  digitalWrite(motordriveENB, LOW);

  digitalWrite(motordriveIN1, LOW);
  digitalWrite(motordriveIN2, LOW);
  digitalWrite(motordriveIN3, LOW);
  digitalWrite(motordriveIN4, LOW);
}

void servocenter() {
  scanservo.write(90);
  delay(500);
}

void servoleft() {
  scanservo.write(150);
  delay(600);
}

void servoright() {
  scanservo.write(30);
  delay(600);
}

float measureDistance() {
  float total = 0;
  int validReadings = 0;

  for (int i = 0; i < 3; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);

    if (duration > 0) {
      float distance = duration * 0.034 / 2;

      if (distance > 2 && distance < 400) {
        total += distance;
        validReadings++;
      }
    }

    delay(30);
  }

  if (validReadings == 0) {
    return 999;
  }

  return total / validReadings;
}