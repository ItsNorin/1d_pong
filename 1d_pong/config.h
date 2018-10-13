#ifndef _CONFIG_H_
#define _CONFIG_H_

// LED Bar pins
#define LED_BAR_COUNT 20
const int LED_BAR_PINS[LED_BAR_COUNT] = {
  PB8, PA1, PA2, PA3, PA4, PB9, PA6, PB0, PB1, PB10,
  PB12, PB13, PB14, PB15, PA8, PA11, PA12, PB5, PB6, PB7
};

// Buttons
#define P_LEFT  0
#define P_RIGHT 1

#define SWT_PIN_L PA5
#define SWT_PIN_R PA0

// Randomization
#define RANDPIN PA7


// timing in millis
#define BUTTON_TIMEOUT 50
#define END_MIN_SCORE_TIME 1000

enum {SLOW = 70, AVG = 50, FAST = 30}; // ball speed

#endif
