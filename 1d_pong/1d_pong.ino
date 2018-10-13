#include "animations.h"
#include "interface.h"
#include "Ball.h"

// GAME 
enum {INIT, START, PLAY, GAMEOVER, END} gameState;
int scores[2];
unsigned long playStart; // keeping time for loop

Ball ball; 


void setup() {
  // enabling all used pins
  for(int i = 0; i < LED_BAR_COUNT; i++)
    pinMode(LED_BAR_PINS[i], OUTPUT);

  pinMode(SWT_PIN_L, INPUT);
  pinMode(SWT_PIN_R, INPUT);

  // starting ball direction randomization
  pinMode(RANDPIN, INPUT_ANALOG); 
  randomSeed(analogRead(RANDPIN));

  lastFlashTime = timePressedL = timePressedR = millis(); // timekeeping
  gameState = INIT;
  lastFlashState = LOW;
}

void loop() {
 switch (gameState) {
  case INIT: // initialize new game
    scores[P_LEFT] = scores[P_RIGHT] = 0;
    ball.dir = random(0,2);
    gameState = START;
    break;
    
  case START: // start round
    setAll(LOW);
    wipeFromCenter(40,HIGH,7);
    waitForBoth(); // wait until both players press button
    wipeRepeat();
    
    ball.resetBall();
    gameOver = false;
    gameState = PLAY;
    break;
    
  case PLAY: // play a round
    ball.updatePos();
    
    if(pressedL() && ball.dir == 0)
      ball.hitLeft();

    if(pressedR() && ball.dir == 1)
      ball.hitRight();
      
    if(gameOver) 
      gameState = GAMEOVER;
    
    break;
    
  case GAMEOVER: // round over
    scores[!ball.dir]++; // increase score of winner
    
    // if either player has a score > 3, game is over
    if(scores[0] >= 3 || scores[1] >= 3) 
      gameState = END;
    else {
      showScores(scores, 7); // if noone has one, show scores
      gameState = START;
    }
   
    break;
    
  case END: // a player has won
    wipeToCenter(40,HIGH);
    wipeToCenter(40,LOW);
    wipeFromCenter(40,HIGH,7);
    // flashes scores until both players press buttons
    int endStartTime = millis();
    bool wait[2] = {0,0};
    while (!wait[0] || !wait[1] || millis() - endStartTime < END_MIN_SCORE_TIME) { 
      if (digitalRead(SWT_PIN_L) == LOW) 
        wait[P_LEFT] = true;
      if (digitalRead(SWT_PIN_R) == LOW) 
        wait[P_RIGHT] = true;
      
      flashScores(scores); // flashes whenever necessary
    }
    wipeToCenter(40,HIGH);
    wipeToCenter(40,LOW);
    timePressedL = timePressedR = 0; // make sure buttons have to be re-pressed
    gameState = INIT;
    break;
  }

}
