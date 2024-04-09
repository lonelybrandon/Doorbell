#include <IRremote.h>

const int RECV_PIN = 11;  // Pin connected to the IR receiver
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();  // Start the IR receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);  // Print the received hex code
    irrecv.resume();  // Receive the next value
  }
}
