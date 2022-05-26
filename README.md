# arduino-hid-examples
Experiments in HID devices with consumer-grade microcontrollers

## Flight simulation
To enhance realism and practice procedures as a pilot would do in a real aircraft, it is sensible to
mimic real equipment as closely as possible. The TeensyControls plugin is by far the easiest method
to interface real hardware with X-Plane.

### Hardware resources
- Rotary encoders: [Amazon](https://www.amazon.com/gp/product/B0177VGSQY/)
- Artemis ATP board: [Sparkfun](https://www.sparkfun.com/products/15442) — Note: would not recommend this board. Its circuit design and pinout is highly confusing and is poorly documented overall.
- Teensy LC: [PJRC](https://www.pjrc.com/store/teensylc.html)

### Libraries
- TeensyControls plugin for X-Plane: [PJRC](https://www.pjrc.com/teensy/td_flightsim.html) • [github](https://github.com/PaulStoffregen/X-Plane_Plugin)
- Teensy Encoder library (included with Teensy installer): [PJRC](https://www.pjrc.com/teensy/td_libs_Encoder.html) • [github](https://github.com/PaulStoffregen/Encoder)

### Notes: Previous iterations
It is reasonably easy to use the standard Arduino USB Joystick libraries, and any combination of
switches and buttons, to control X-Plane. I built a switch panel with SPST switches, debounced
with [Bounce2](https://www.arduino.cc/reference/en/libraries/bounce2/), and designed the code
such that a rising/falling event would send a Joystick button press.

However, it felt hacky to do this because the problem is synchronizing the initial state of the
switches with the initial state of X-Plane. There are too many caveats which end up with switches
accidentally showing the opposite indication of the simulated switch state.

Bidirectional communication as provided by PaulStoffregen's libraries allow us to write the code in
a much more declarative way, and to use a metaphor from web development, the microcontroller acts
like a functional component in React that updates the state of its parent.
