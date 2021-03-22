/**
 * You must select Digigroove from the "Tools > USB Type" menu
 * Code modified copypasta from "Buttons to USB Joystick Example"
 *
 * The Digigroove types are created by modifying code Arduino libraries...
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

  Digigroove.useManualSend(true); // single packet with all buttons at same time
}

// Pins are wired as as 7 left, 7 right; otherwise mostly random!
void button(int pin, boolean on) {
  if (pin >= 0 && pin <= 6) {
      Digigroove.button(pin+1, on ? 1 : 0, true);
      /*
      if (pin > 0 && pin <= 4)
        digitalWrite(BUTTON_MAX + pin, on ? LOW : HIGH);
      */
  } else if (pin > 6 && pin <= 13) {
      Digigroove.button(pin-6, on ? 1 : 0, false);
      /*
      if (pin > 6 && pin <= 10)
        digitalWrite(BUTTON_MAX + pin - 2, on ? LOW : HIGH);
      */
  }
}

void loop() {
  int i;
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  for (i = 0; i < BUTTON_MAX; i++) {
    buttons[i]->update();

    // Check each button for "falling" edge.
    // Update the Digigroove buttons only upon changes.
    // falling = high (not pressed - voltage from pullup resistor)
    //           to low (pressed - button connects pin to ground)
    if (buttons[i]->fallingEdge())
      button(i, true);

    // Check each button for "rising" edge
    // Update the Digigroove buttons only upon changes.
    // rising = low (pressed - button connects pin to ground)
    //          to high (not pressed - voltage from pullup resistor)
    if (buttons[i]->risingEdge())
      button(i, false);
  }

  Digigroove.send_now();
}
