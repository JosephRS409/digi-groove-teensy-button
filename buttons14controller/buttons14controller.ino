/**
 * You must select Joystick from the "Tools > USB Type" menu
 * Code modified copypasta from "Buttons to USB Joystick Example"
 *
 * Note that the USB configuration probably doesn't support turning on the
 * LEDs from the computer with a custom driver right now, so no improvement
 * at present over inline wiring for the LEDs.
 *
 * Copyright © 2015 Michael Clark <iiridayn@gmail.com>
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
 */
#include <Bounce.h>

#define BUTTON_MAX 14
#define LED_MAX BUTTON_MAX + 10 // 14-23

Bounce *buttons[BUTTON_MAX];

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
  for (i = 0; i < BUTTON_MAX; i++) {
    pinMode(i, INPUT_PULLUP);

    // Create Bounce objects for each button.  The Bounce object
    // automatically deals with contact chatter or "bounce", and
    // it makes detecting changes very simple.
    //Bounce button0 = Bounce(buttonInputPin, 10);
    buttons[i] = new Bounce(i, 10);
  }

  for (i = BUTTON_MAX; i < LED_MAX; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  int i;
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  for (i = 0; i < BUTTON_MAX; i++) {
    buttons[i]->update();

    // Check each button for "falling" edge.
    // Update the Joystick buttons only upon changes.
    // falling = high (not pressed - voltage from pullup resistor)
    //           to low (pressed - button connects pin to ground)
    if (buttons[i]->fallingEdge()) {
      Joystick.button(i+1, 1);
      if (BUTTON_MAX+i < LED_MAX) {
        digitalWrite(BUTTON_MAX+i, LOW);
      }
    }

    // Check each button for "rising" edge
    // Update the Joystick buttons only upon changes.
    // rising = low (pressed - button connects pin to ground)
    //          to high (not pressed - voltage from pullup resistor)
    if (buttons[i]->risingEdge()) {
      Joystick.button(i+1, 0);
      if (BUTTON_MAX+i < LED_MAX) {
        digitalWrite(BUTTON_MAX+i, HIGH);
      }
    }
  }
}
