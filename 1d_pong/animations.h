#include "config.h"

unsigned long lastFlashTime;
bool lastFlashState;

// set all LEDS to given state
void setAll(bool state = LOW) {
  for(int i = 0; i < LED_BAR_COUNT; i++)
    digitalWrite(LED_BAR_PINS[i], state);
}

// sets leds from edges to center to given state
void wipeToCenter(const int rate, const bool state, const int amount = LED_BAR_COUNT/2, const int border = 0) {
  for(int i = border; i < amount; i++) {
    delay(rate);
    digitalWrite(LED_BAR_PINS[i], state);
    digitalWrite(LED_BAR_PINS[19 - i], state);
  }
}

// sets leds from center to edges to given state
void wipeFromCenter(const int rate, const bool state, const int amount = LED_BAR_COUNT/2, const int border = 0) {
  for(int i = 0; i < amount - border; i++) {
    delay(rate);
    digitalWrite(LED_BAR_PINS[10+i], state);
    digitalWrite(LED_BAR_PINS[9-i], state);
  }
}

// wipe back and forth times times with given rate modifier speedMultip 
void wipeRepeat(int times = 3, const int speedMultip = 10) {
  for(; times > 1; times--) { // animate starting
    wipeToCenter(times*speedMultip,LOW);
    wipeFromCenter(times*speedMultip-(speedMultip/2),HIGH);
  }
  wipeToCenter(speedMultip, LOW);
}

// wipe that represents a game over
void gameOverWipe() {
  wipeToCenter(40,HIGH);
  wipeToCenter(40,LOW);
  wipeFromCenter(40,HIGH);
  wipeFromCenter(40,LOW, 10);
}

// attempts to flash scores, returns true if flashed, otherwise false
bool flashScores(int scores[2]) {
  if(millis() - lastFlashTime > ((lastFlashState) ? 25 : 75)) {
    for (int j = 0; j < scores[0]; j++)
      digitalWrite(LED_BAR_PINS[j], lastFlashState);
    for (int j = 0; j < scores[1]; j++)
      digitalWrite(LED_BAR_PINS[19-j], lastFlashState);
      
    lastFlashState = !lastFlashState;
    lastFlashTime = millis();
    return true;
  }
  return false;
}

// flashes scores 7 times
void showScores(int scores[2], int flashes = 7) {
  for (int i = 0; i < flashes*2; i++)
    while(!flashScores(scores)); // ensures 7 flashes
  setAll(LOW);
}

// show whether players are ready
void showReady(const bool left, const bool right) {
  for (int i = 3; i < 10; i++) {
    digitalWrite(LED_BAR_PINS[i], left);
    digitalWrite(LED_BAR_PINS[19 - i], right);
  }
}

