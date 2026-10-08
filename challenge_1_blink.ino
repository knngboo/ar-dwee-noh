// ===================== CHALLENGE 1: BLINK =====================
// CIRCUIT: LED on pin 9. Pin 9 -> resistor -> LED long leg.
//          LED short leg -> GND.
//
// GOAL:    The LED on pin 9 blinks: 1 second on, 1 second off.
// PROBLEM: It uploads fine, but the LED looks like it's always on.
// HINT:    Walk through loop() one line at a time. What happens
//          right after the LED turns off?
//
// DONE EARLY? Make it blink SOS in Morse code:
//          3 short blinks, 3 long blinks, 3 short blinks, then a pause.
// ==============================================================

void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
}
