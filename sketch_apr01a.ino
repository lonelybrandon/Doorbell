#include <Servo.h>
#include <IRremote.h>
#include <LiquidCrystal.h>

#define IR_RECEIVE_PIN 6
#define TRIGGER_PIN 8
#define ECHO_PIN 9
#define LED2 7
#define LED3 13
decode_results results;
LiquidCrystal lcd(11, 10, 5, 4, 3, 2);
int i = 0;
int buttonPressed = -1; 
String password = "123456";
String pad;
char buttonpressed;
int duration = 0;
int distance = 0;
Servo s1;
void setup() {
  Serial.begin(9600);
  IrReceiver.enableIRIn();
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  s1.attach(12);
}

void loop() {
  if (IrReceiver.decode()) {
    switch (IrReceiver.decodedIRData.command)
    {
      case 0xF30CFF00:
        buttonPressed = 1; 
        break;
      
      default:
        buttonPressed = -1; 
        break;
    }   
    addDigit(buttonPressed);
    IrReceiver.resume();
  }
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 28.5;
  Serial.println(distance);
  if ( distance <= 10){
    digitalWrite(LED3, HIGH);
    lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Enter Passcode: ");
  }
  else{
    digitalWrite(LED3, LOW);
  }
   if ( distance <= 30){
    digitalWrite(LED2, HIGH);
  }
  else{
    digitalWrite(LED2, LOW);
  }
}
  void addDigit(char digit) {
  lcd.setCursor(i, 1);
  lcd.print(digit);
  i++;
  pad += digit;
  
  if (pad.length() == password.length()) {
    if (pad == password) {
      lcd.setCursor(0, 1);
      lcd.print("Access Granted");
       s1.write(180);
    delay(3000);
    s1.write(0);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Incorrect");
    }
    delay(2000); 
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print("Enter Passcode: ");
    pad = ""; 
    i = 0;    
  }
}
