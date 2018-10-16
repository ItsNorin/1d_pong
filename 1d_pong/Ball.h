#include "config.h"

bool gameOver;
bool winner;

class Ball {
public: 
  int ballRate; // milliseconds between each ball movement
  bool dir; // direction of ball
  int ballPos; // position of ball on field
  unsigned long lastMoveTime; // when ball moved last
  unsigned long roundStart;
  const int SPEEDS[3] = {FAST, AVG, SLOW};
  
  // reset the ball
  void resetBall(){
    ballRate = SLOW;
    ballPos = (dir)? 9 : 10;
    lastMoveTime = millis();
  }
  
  Ball() : dir(0) {
    resetBall();
  }

  // start timer to increase speed
  void startMatch() {
    roundStart = millis();
  }

  // get speed increase over time (+1 ms every 5 seconds)
  int getSpeedMod() {
    return (millis() - roundStart) / 5000;
  }
  
  // updates position of ball, also sets game over state
  void updatePos(){
    if (!gameOver) {
      if (millis() > lastMoveTime + ballRate - getSpeedMod()) { // if enough time has elapsed, move the ball, otherwise make sure its lit
        lastMoveTime = millis();
        digitalWrite(LED_BAR_PINS[ballPos], LOW);
        
        (dir) ? ballPos++ : ballPos--; // change ball position
          
        if (ballPos >= LED_BAR_COUNT) { // if ball left the field, end game and declare winner
          winner = P_LEFT;
          gameOver = true;
        }
        else if (ballPos < 0) {
          winner = P_RIGHT;
          gameOver = true;
        }
        else
          digitalWrite(LED_BAR_PINS[ballPos], HIGH);
      }
      else 
        digitalWrite(LED_BAR_PINS[ballPos], HIGH);
    }
  }
  
  // attempt to hit ball from right side
  void hitRight() {
    if(ballPos <= 19 && ballPos >= 17) {
      dir = !dir;
      ballRate = SPEEDS[19 - ballPos];
    }
  }
  
  // attempt to hit ball from left side
  void hitLeft() {
    if(ballPos >= 0 && ballPos <= 2) {
      dir = !dir;
      ballRate = SPEEDS[ballPos];
    }
  }
};
