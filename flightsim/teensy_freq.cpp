#include <Bounce.h>
#include <Encoder.h>
#include <ParallaxLCD.h>

//Bounce buttonUp = Bounce(3, 5);      // Pushbutton on pin 3, 5ms debounce
//Bounce buttonDown = Bounce(4, 5);    // Pushbutton on pin 4, 5ms debounce
Encoder wheelCoarse = Encoder(11, 12);       // Rotary Encoder
Encoder wheelFine = Encoder(10, 9);       // Rotary Encoder
ParallaxLCD lcd(8,2,16);

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
  lcd.setup();
  delay(1000);
  lcd.on();
  lcd.empty();
  lcd.backLightOn();
  lcd.at(1,3,"Hello World!");
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
