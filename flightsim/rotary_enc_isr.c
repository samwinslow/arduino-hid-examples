// Reads rotary encoder using interrupt routines
// Author: samwinslow

// Designed and tested on Artemis ATP; may work on other boards
// For now, closed switch is HIGH (debounced with external pull-down resistors)
// because not all digital inputs support INPUT_PULLDOWN on the Artemis ATP.

#define PIN_A 2
#define PIN_B 1
#define PIN_COM 17

volatile int count = 0;
volatile byte a = 0;
volatile byte b = 0;

void setup() {
  Serial.begin(115200);

  // Write HIGH to common of device
  pinMode(PIN_COM, OUTPUT);
  digitalWrite(PIN_COM, HIGH);

  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);

  attachInterrupt(PIN_B, isrCLK, CHANGE);
}

void loop() {
  Serial.println(count);
}

void isrCLK() {
  a = digitalRead(PIN_A);
  b = digitalRead(PIN_B);
  if (a != b) {
    count--;
  } else {
    count++;
  }
}
