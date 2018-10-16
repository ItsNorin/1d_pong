#include "animations.h"

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
    if (pressedL()) wait[P_LEFT] = true;
    if (pressedR()) wait[P_RIGHT] = true;
    showReady(wait[P_LEFT], wait[P_RIGHT]);
  }
}




