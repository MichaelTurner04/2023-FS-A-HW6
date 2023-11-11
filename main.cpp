#include <iostream>
#include "gal.h"
using namespace std;

int main() {
  srand(715);
  point player_x, player_y, alien_x, alien_y, power_x, power_y, guess_x, guess_y, player_last_x,player_last_y;
  int humanLives = 6;
  int alienLives = 12;
  int bullets = 20;
  int round = 0;
  int immunity_duration = 0;
  string powerUp;

  cout << "Welcome to GalDef - The Galactic Defender! \nThe game starts now!\nYou have 5 lives and 15 bullets to begin with, the alien has 10 lives and will try to attack you! Goodluck, Let the game begin…!!!\n" << endl;
  generatePowerUpPosition(power_x, power_y);
  do{
    cout << "\nRound "<<++round << endl;
    generatePlayerPosition(player_x, player_y,player_last_x, player_last_y);
    generateAlienPosition(alien_x, alien_y,player_x, player_y);
    
    for(int i=0; i<2; i++){ //runs shoot alien function 2 times 
      shootAlien(guess_x, guess_y, alien_x, alien_y, alienLives, bullets,humanLives, player_x, player_y);
    }
    acquirePowerUp(power_x, power_y,  player_x, player_y, humanLives, bullets, immunity_duration, powerUp); //checks if player is on the same spot as the power up
if(round != 1){ //if not the first round, the alien gets a turn to damage the player based on its last position
  shootPlayer(player_last_x, player_last_y, alien_x, alien_y, humanLives, immunity_duration);
}
    
    displayGameStatus(humanLives, alienLives, bullets, powerUp,player_x, player_y, alien_x, alien_y);
  }while (humanLives >0 && alienLives >0 & bullets >0);
  
  if(humanLives ==0){
    cout << "You died, The alien continues to roam and terrorize the galaxy!";
    return 0;
  }else if(alienLives == 0){
    cout << "The alien has been defeated! Congratulations, player! You Saved the galaxy! \nThanks for playing GalDef!";
    return 0;
  }else if(bullets == 0){
  cout << "You ran out of bullets, The alien continues to roam and terrorize the galaxy!";
  return 0;
  }
  return 0;
}