#include <Bounce.h>
#include <Encoder.h>

// TODO: ACTIVE / STBY toggle button
// TODO: COMM / VLOC toggle button
// TODO: Parallax LCD library

//Bounce buttonUp = Bounce(3, 5);      // Pushbutton on pin 3, 5ms debounce
//Bounce buttonDown = Bounce(4, 5);    // Pushbutton on pin 4, 5ms debounce
Encoder wheelCoarse = Encoder(11, 12);       // Rotary Encoder
Encoder wheelFine = Encoder(10, 9);       // Rotary Encoder
//DogLcd lcd = DogLcd(10, 9, 7, 8);    // DogM LCD on pins 7, 8, 9, 10

// X-Plane objects, 3 command refs and 1 data ref
FlightSimCommand ComCoarseUp;
FlightSimCommand ComCoarseDown;
FlightSimCommand ComFineUp;
FlightSimCommand ComFineDown;
FlightSimInteger ComFrequencyHz;

// variables
long encoder_prev_coarse=0;
long encoder_prev_fine=0;

void setup() {
  // initialize all hardware
//  pinMode(3, INPUT_PULLUP);  // input pullup mode allows connecting
//  pinMode(4, INPUT_PULLUP);  // buttons and switches from the pins
//  pinMode(9, INPUT_PULLUP);  // to ground, and the chip provide the
//  pinMode(10, INPUT_PULLUP);  // required pullup resistor :-)
//  lcd.begin(DOG_LCD_M162);
//  lcd.print("com1:");

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

// TODO: read the pushbuttons, and send X-Plane commands when they're pressed
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
//
//// write a number onto the LCD, first row, starting at 6th column
//void update_lcd(long val)
//{
//  lcd.setCursor(6, 0);
//  lcd.print(val);
//  lcd.print("  ");
//}