#define HWSERIAL Serial3
#define WRITE_BASE   128
#define COL_SIZE    16

#include <Bounce.h>
#include <Encoder.h>

//Bounce buttonUp = Bounce(3, 5);      // Pushbutton on pin 3, 5ms debounce
//Bounce buttonDown = Bounce(4, 5);    // Pushbutton on pin 4, 5ms debounce
Encoder wheelCoarse = Encoder(11, 12);       // Rotary Encoder
Encoder wheelFine = Encoder(10, 9);       // Rotary Encoder

// X-Plane objects, 3 command refs and 1 data ref
FlightSimCommand ComCoarseUp;
FlightSimCommand ComCoarseDown;
FlightSimCommand ComFineUp;
FlightSimCommand ComFineDown;
FlightSimInteger ComFrequencyHz;

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

void setup() {
  HWSERIAL.begin(19200);
  delay(500);
  HWSERIAL.write(24); // on
  delay(50);

  lcdEmpty();
  lcdPrintAt(1, 3, "COM1        STBY");

  //  lcd.on();
  //  lcd.empty();
  //  lcd.backLightOn();
  //  lcd.at(1, 3, "");


  // configure the X-Plane variables
  ComCoarseUp = XPlaneRef("sim/radios/stby_com1_coarse_up");
  ComCoarseDown = XPlaneRef("sim/radios/stby_com1_coarse_down");
  ComFineUp = XPlaneRef("sim/radios/stby_com1_fine_up");
  ComFineDown = XPlaneRef("sim/radios/stby_com1_fine_down");
  ComFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/com1_frequency_hz");
  //  ComFrequencyHz.onChange(update_lcd);  // update the LCD when X-Plane changes

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

  // read the pushbuttons, and send X-Plane commands when they're pressed
  //  buttonUp.update();
  //  buttonDown.update();
  //  if (buttonUp.fallingEdge()) {
  //    ComCoarseUp = 1;
  //  }
  //  if (buttonUp.risingEdge()) {
  //    ComCoarseUp = 0;
  //  }
  //  if (buttonDown.fallingEdge()) {
  //    ComCoarseDown = 1;
  //  }
  //  if (buttonDown.risingEdge()) {
  //    ComCoarseDown = 0;
  //  }
}
