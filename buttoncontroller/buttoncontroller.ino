/* You must select Joystick from the "Tools > USB Type" menu */
#include <Bounce.h>

const int buttonInputPin = 2;
const int ledPin = 11;

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
Bounce button0 = Bounce(buttonInputPin, 10);

void setup() {
  // Configure the pins for input mode with pullup resistors.
  // The pushbuttons connect from each pin to ground.  When
  // the button is pressed, the pin reads LOW because the button
  // shorts it to ground.  When released, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.  LOW for "on", and HIGH for "off" may seem
  // backwards, but using the on-chip pullup resistors is very
  // convenient.  The scheme is called "active low", and it's
  // very commonly used in electronics... so much that the chip
  // has built-in pullup resistors!
  pinMode(buttonInputPin, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button0.update();

  // Check each button for "falling" edge.
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)
  if (button0.fallingEdge()) {
    Joystick.button(1, 1);
    digitalWrite(ledPin, LOW);
  }
  
  // Check each button for "rising" edge
  // Update the Joystick buttons only upon changes.
  // rising = low (pressed - button connects pin to ground)
  //          to high (not pressed - voltage from pullup resistor)
  if (button0.risingEdge()) {
    Joystick.button(1, 0);
    digitalWrite(ledPin, HIGH);
  }
}
