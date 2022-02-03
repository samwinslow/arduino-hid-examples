// Reads rotary encoder using interrupt routines
// Author: samwinslow

// Designed and tested on Artemis ATP; may work on other boards
// For now, closed switch is HIGH (debounced with external pull-down resistors)
// because not all digital inputs support INPUT_PULLDOWN on the Artemis ATP.

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
int encoder_values[encoders_count] = {0};

void read_encoder(int index) {
  auto encoder = ALL_ENCODERS[index];
  byte a = digitalRead(encoder[0]);
  byte b = digitalRead(encoder[1]);
  if (a != b) {
    // decrement HSI value
  } else {
    // increment HSI value
  }
}

void isr_HSI() {
  read_encoder(0);
}
void isr_HDG1() {
  read_encoder(1);
}
void isr_HDG2() {
  read_encoder(2);
}
void isr_ATTD() {
  read_encoder(3);
}
void isr_CDI1() {
  read_encoder(4);
}
void isr_CDI2() {
  read_encoder(5);
}
void isr_ASPD() {
  read_encoder(6);
}
void isr_ALTM() {
  read_encoder(7);
}

//int (*isrs[encoders_count]) (void);

void loop() {
  //  Send encoder values over serial
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < encoders_count; i++) {
    pinMode(ALL_ENCODERS[i][0], INPUT);
    pinMode(ALL_ENCODERS[i][1], INPUT);
  }
  pinMode(HDG1_S, INPUT);

  attachInterrupt(HSI_B, isr_HSI, CHANGE);
  attachInterrupt(HDG1_B, isr_HDG1, CHANGE);
  attachInterrupt(HDG2_B, isr_HDG2, CHANGE);
  attachInterrupt(ATTD_B, isr_ATTD, CHANGE);
  attachInterrupt(CDI1_B, isr_CDI1, CHANGE);
  attachInterrupt(CDI2_B, isr_CDI2, CHANGE);
  attachInterrupt(ASPD_B, isr_ASPD, CHANGE);
  attachInterrupt(ALTM_B, isr_ALTM, CHANGE);
}
