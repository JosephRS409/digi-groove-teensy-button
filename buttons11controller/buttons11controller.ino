/**
 * You must select Joystick from the "Tools > USB Type" menu
 * Code modified copypasta from "Buttons to USB Joystick Example"
 */
#include <Bounce.h>

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
//Bounce button0 = Bounce(buttonInputPin, 10);
Bounce buttons[11] = {
  Bounce(0, 10),
  Bounce(1, 10),
  Bounce(2, 10),
  Bounce(3, 10),
  Bounce(4, 10),
  Bounce(5, 10),
  Bounce(6, 10),
  Bounce(7, 10),
  Bounce(8, 10),
  Bounce(9, 10),
  Bounce(10, 10),
};

void setup() {
  int i;
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
  for (i = 0; i <= 10; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  for (i = 11; i <= 21; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  int i;
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  for (i = 0; i <= 10; i++) {
    buttons[i].update();
  
    // Check each button for "falling" edge.
    // Update the Joystick buttons only upon changes.
    // falling = high (not pressed - voltage from pullup resistor)
    //           to low (pressed - button connects pin to ground)
    if (buttons[i].fallingEdge()) {
      Joystick.button(i+1, 1);
      digitalWrite(i+11, LOW);
    }
    
    // Check each button for "rising" edge
    // Update the Joystick buttons only upon changes.
    // rising = low (pressed - button connects pin to ground)
    //          to high (not pressed - voltage from pullup resistor)
    if (buttons[i].risingEdge()) {
      Joystick.button(i+1, 0);
      digitalWrite(i+11, HIGH);
    }
  }
}
