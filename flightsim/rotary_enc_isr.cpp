// Reads rotary encoder using interrupt routines
// Author: samwinslow

// Designed and tested on Artemis ATP; may work on other boards
// For now, closed switch is HIGH (debounced with external pull-down resistors)
// because not all digital inputs support INPUT_PULLDOWN on the Artemis ATP.

//volatile int count = 0;
//volatile byte a = 0;
//volatile byte b = 0;
//
//void setup() {
//  Serial.begin(115200);
//
//  // Write HIGH to common of device
//  pinMode(PIN_COM, OUTPUT);
//  digitalWrite(PIN_COM, HIGH);
//
//  pinMode(PIN_A, INPUT);
//  pinMode(PIN_B, INPUT);
//
//  attachInterrupt(PIN_B, isrCLK, CHANGE);
//}

#define countof(a) (sizeof(a) / sizeof(a[0]))

#define HSI_A  3
#define HDG1_S 18 // Single momentary switch
#define HDG1_B 19
#define HSI_B  15
#define ATTD_B 26
#define CDI1_A 9
#define HDG1_A 10
#define CDI2_B 8
#define CDI2_A 14
#define ASPD_B 42
#define ATTD_A 43
#define HDG2_A 0
#define HDG2_B 1
#define ALTM_A 2
#define ALTM_B 45
#define CDI1_B 41
#define ASPD_A 17

#define HSI  {HSI_A, HSI_B}
#define HDG1 {HDG1_A, HDG1_B}
#define HDG2 {HDG2_A, HDG2_B}
#define ATTD {ATTD_A, ATTD_B}
#define CDI1 {CDI1_A, CDI1_B}
#define CDI2 {CDI2_A, CDI2_B}
#define ASPD {ASPD_A, ASPD_B}
#define ALTM {ALTM_A, ALTM_B}

const int ALL_ENCODERS[][2] = {HSI, HDG1, HDG2, ATTD, CDI1, CDI2, ASPD, ALTM};

const int encoders_count = countof(ALL_ENCODERS);

void loop() {
  //  Serial.println(count);
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < encoders_count; i++) {
    auto& [a, b] = ALL_ENCODERS[i];
    pinMode(a, INPUT);
    pinMode(b, INPUT);
  }

  pinMode(HDG1_S, INPUT);
}
//
//void isrCLK() {
//  a = digitalRead(PIN_A);
//  b = digitalRead(PIN_B);
//  if (a != b) {
//    count--;
//  } else {
//    count++;
//  }
//}
