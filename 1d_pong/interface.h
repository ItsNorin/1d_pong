#include "config.h"

unsigned long timePressedL, timePressedR;

bool pressedL() {
  bool state = false;
  if(digitalRead(SWT_PIN_L)) {
    timePressedL = millis(); // reset time if button isn't pressed
  }
  else {
    if(millis() - timePressedL < BUTTON_TIMEOUT)
      state = true;
    timePressedL = 0;
  }
  return state;
}

bool pressedR() {
  bool state = false;
  if(digitalRead(SWT_PIN_R)) { 
    timePressedR = millis(); // reset time if button isn't pressed
  }
  else {
    if(millis() - timePressedR < BUTTON_TIMEOUT)
      state = true;
    timePressedR = 0;
  }
  return state;
}

// wait until both players press button
void waitForBoth() {
  bool wait[2] = {0,0};
  while (!wait[0] || !wait[1]) {
    if (pressedL()) 
      wait[P_LEFT] = true;
    if (pressedR()) 
      wait[P_RIGHT] = true;
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_BAR_PINS[i], wait[P_LEFT]);
      digitalWrite(LED_BAR_PINS[19 - i], wait[P_RIGHT]);
    }
  }
}



