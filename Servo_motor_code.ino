#include <Servo.h>

#define IR_RECEIVE_PIN 6
#define TRIGGER_PIN 8
#define ECHO_PIN 9
#define LED2 7
#define LED3 13

decode_results results;
int buttonPressed = -1; 
String password = "123456";
String pad;
char buttonpressed;
int duration = 0;
int distance = 0;
bool passcodeDisplayed = false; 
Servo s1;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  s1.attach(12); 
}

void loop() {
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 28.5;
  Serial.println(distance);
  
  if (distance <= 10 && !passcodeDisplayed) {
    digitalWrite(LED3, HIGH);
    passcodeDisplayed = true; 
    s1.write(180); 
  } else if (distance > 10 && passcodeDisplayed) {
    passcodeDisplayed = false; 
    digitalWrite(LED3, LOW); 
    s1.write(0); 
  }
  
  if (distance <= 30) {
    digitalWrite(LED2, HIGH);
  } else {
    digitalWrite(LED2, LOW);
  }
}
