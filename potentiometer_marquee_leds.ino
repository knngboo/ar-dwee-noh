/*
  Sketch to run a set of LEDs on an Arduino in a marquee pattern, with a speed set by a potentiometer.
*/
// The digital pins to use for the LEDS
const uint8_t PATTERN_LEDS[] = {2, 3, 4, 6, 8, 10};
// The pin the potentiometer is connected to
const int POTENTIOMETER_PIN = PIN_A1;
// The minimum delay (fastest speed) the marquee runs at. Corresponds to step 0.
const unsigned int BASE_DELAY_MS = 50;
// The maximum delay (slowest speed) the marquee runs at. Corresponds to the maximum step.
const unsigned int MAX_DELAY_MS = 1000;
// The number of steps to extract from the ADC, with 0 corresponding to ADC value 0, and POTENTIOMETER_STEPS corresponding to ADC value 1024.
const unsigned int POTENTIOMETER_STEPS = 15;
// The number of LEDs to light in each direction from the current state (position) of the marquee.
const int LIGHT_WITHIN_DISTANCE = 1;

const unsigned int POTENTIOMETER_STEP_MS = (MAX_DELAY_MS - BASE_DELAY_MS) / POTENTIOMETER_STEPS;
const int NUM_PATTERN_LEDS = sizeof(PATTERN_LEDS) / sizeof(uint8_t);

int state = 0;
int ticksSinceUpdate = 0;

void setup() 
{
  Serial.begin(115200);
  for (size_t i = 0; i < NUM_PATTERN_LEDS; i++) {
    pinMode(PATTERN_LEDS[i], OUTPUT);
    digitalWrite(PATTERN_LEDS[i], 0);
  }
}

void writeLedsForState()
{
  int startPosition = state - LIGHT_WITHIN_DISTANCE;
  int endPosition = state + LIGHT_WITHIN_DISTANCE;

  if (startPosition < 0) {
    startPosition = NUM_PATTERN_LEDS + startPosition;
  } else if (startPosition >= NUM_PATTERN_LEDS) {
    startPosition -= NUM_PATTERN_LEDS;
  }
  if (endPosition < 0) {
    endPosition = NUM_PATTERN_LEDS + endPosition;
  } else if (endPosition >= NUM_PATTERN_LEDS) {
    endPosition -= NUM_PATTERN_LEDS;
  }

  for (int i = 0; i < NUM_PATTERN_LEDS; i++) {
    bool shouldLight;

    if (endPosition > startPosition) {
      shouldLight = i >= startPosition && i <= endPosition;
    } else {
      shouldLight = i <= endPosition || i >= startPosition;
    }

    digitalWrite(PATTERN_LEDS[i], shouldLight ? 1 : 0);
  }
}

void loop() {
  const int currentPotentiometerStep = round((static_cast<float>(analogRead(POTENTIOMETER_PIN)) / 1024) * POTENTIOMETER_STEPS);
  const int currentDelay = BASE_DELAY_MS + currentPotentiometerStep * POTENTIOMETER_STEP_MS;

  Serial.print("Current potentiometer step: ");
  Serial.print(currentPotentiometerStep);
  Serial.print(" / ");
  Serial.print(POTENTIOMETER_STEPS);
  Serial.print(" (");
  Serial.print(currentDelay);
  Serial.println(" ms)");
  delay(currentDelay);
  state = (state + 1) % NUM_PATTERN_LEDS;
  writeLedsForState();
}
