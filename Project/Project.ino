#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
int trigPin = 9;
int echoPin = 10;
int timeInMicro;
int distance;
int seconds = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16,2);
  lcd.print("Project");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  timeInMicro = pulseIn(echoPin,HIGH);
  distance = timeInMicro*0.034/2;
  lcd.setCursor(0,1);
  lcd.print(seconds);
  delay(1000);
  seconds += 1;
}
