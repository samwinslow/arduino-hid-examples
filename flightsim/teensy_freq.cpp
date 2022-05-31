#define HWSERIAL Serial3
#define WRITE_BASE   128
#define COL_SIZE    16

#include <Bounce.h>
#include <Encoder.h>

Bounce toggleButton = Bounce(7, 5); // pin 7, 5ms debounce
Encoder wheelCoarse = Encoder(11, 12);
Encoder wheelFine = Encoder(10, 9);

// X-Plane objects, 3 command refs and 1 data ref
FlightSimCommand ComCoarseUp;
FlightSimCommand ComCoarseDown;
FlightSimCommand ComFineUp;
FlightSimCommand ComFineDown;
FlightSimCommand ComStbyFlip;
FlightSimInteger ComFrequencyHz;
FlightSimInteger ComStbyFrequencyHz;

// variables
long encoder_prev_coarse = 0;
long encoder_prev_fine = 0;

void lcdEmpty() {
  HWSERIAL.write(12); // empty
  delay(100);
}

void lcdPos(int col, int row) {
  HWSERIAL.write(WRITE_BASE + (col * COL_SIZE) + row);
}

void lcdPrintAt(int col, int row, char* str) {
  lcdPos(col, row);
  HWSERIAL.print(str);
  HWSERIAL.write(22);
}

void updateActive(long freq) {
  char mhz[3];
  sprintf(mhz, "%lu", freq / 100);
  lcdPrintAt(2, -12, mhz);
  lcdPrintAt(2, -9, ".");
  char khz[2];
  sprintf(khz, "%lu", freq % 100);
  lcdPrintAt(2, -8, khz);
}

void updateStandby(long freq) {
  char mhz[3];
  sprintf(mhz, "%lu", freq / 100);
  lcdPrintAt(2, -2, mhz);
  lcdPrintAt(2, 1, ".");
  char khz[2];
  sprintf(khz, "%lu", freq % 100);
  if (freq % 10 == 0) {
    lcdPrintAt(2, 2, khz);
    lcdPrintAt(2, 3, "0");
  } else if (freq % 100 < 10) {
    lcdPrintAt(2, 2, "0");
    lcdPrintAt(2, 4, khz);
  } else {
    lcdPrintAt(2, 2, khz);
  }
}

void setup() {
  HWSERIAL.begin(19200);
  delay(500);
  HWSERIAL.write(24); // on
  delay(50);

  lcdEmpty();
  lcdPrintAt(1, 3, "COM1        STBY");


  // configure the X-Plane variables
  ComCoarseUp = XPlaneRef("sim/radios/stby_com1_coarse_up");
  ComCoarseDown = XPlaneRef("sim/radios/stby_com1_coarse_down");
  ComFineUp = XPlaneRef("sim/radios/stby_com1_fine_up");
  ComFineDown = XPlaneRef("sim/radios/stby_com1_fine_down");
  ComStbyFlip = XPlaneRef("sim/radios/com1_standy_flip");
  ComFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/com1_frequency_hz");
  ComFrequencyHz.onChange(updateActive);
  ComStbyFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/com1_standby_frequency_hz");
  ComStbyFrequencyHz.onChange(updateStandby);

}

void loop() {
  FlightSim.update();

  long enc_coarse = wheelCoarse.read() / 2;
  if (enc_coarse > encoder_prev_coarse) {
    ComCoarseUp.once();
    encoder_prev_coarse = enc_coarse;
  } else if (enc_coarse < encoder_prev_coarse) {
    ComCoarseDown.once();
    encoder_prev_coarse = enc_coarse;
  }

  long enc_fine = wheelFine.read() / 2;
  if (enc_fine > encoder_prev_fine) {
    ComFineUp.once();
    encoder_prev_fine = enc_fine;
  } else if (enc_fine < encoder_prev_fine) {
    ComFineDown.once();
    encoder_prev_fine = enc_fine;
  }

  toggleButton.update();
  if (toggleButton.fallingEdge()) {
    ComStbyFlip.once();
  }
}
