#include "gal.h"
#include <iostream>
#include <cmath>
using namespace std;

 
void generatePlayerPosition(point & player_x, point &player_y, point &player_last_x, point &player_last_y){
   player_last_x = player_x;
   player_last_y = player_y;
  player_x.m_XCoord = rand() % 4;
  player_y.m_YCoord = rand() %4;
}

void generateAlienPosition(point & alien_x, point &alien_y, point player_x, point player_y){
  alien_x.m_XCoord = rand() % 4;
  alien_y.m_YCoord = rand() %4;
  while( (player_x.m_XCoord == alien_x.m_XCoord) && (player_y.m_YCoord == alien_y.m_YCoord)){ //checks if alien and player are on the same spot
    alien_x.m_XCoord = rand() % 4;
    alien_y.m_YCoord = rand() %4;
  }
}
 
void generatePowerUpPosition(point & power_x, point &power_y){
  
  power_x.m_XCoord = rand() % 4;
  power_y.m_YCoord = rand() %4;
}

void shootAlien(point guess_x, point guess_y, point alien_x, point alien_y, int &alienLives, int &bullets, int &humanLives, point player_x, point player_y){
  static int inARow = 0;
  do{
  cout << "Player, please enter the coordinates to shoot (0-3)(x, y): ";
  cin >> guess_x.m_XCoord >> guess_y.m_YCoord;
  }while((guess_x.m_XCoord > 3 || guess_x.m_XCoord < 0) || (guess_y.m_YCoord > 3 ||guess_y.m_YCoord < 0));
  
  if(guess_x.m_XCoord == alien_x.m_XCoord && guess_y.m_YCoord == alien_y.m_YCoord){
    cout << "You hit the alien! The alien lost 2 lives." << endl;
    alienLives -= 2;
    bullets--;
    inARow++;
    generateAlienPosition(alien_x, alien_y, player_x, player_y);
    cout <<"The alien's position has been refreshed to a new location." << endl;
    
  }else if((abs(guess_x.m_XCoord - alien_x.m_XCoord)  == 1 && guess_y.m_YCoord == alien_y.m_YCoord) || (guess_x.m_XCoord == alien_x.m_XCoord) && abs(guess_y.m_YCoord - alien_y.m_YCoord) == 1){
    cout << "Close guess! The alien lost 1 life." << endl;
    alienLives -=1;
    bullets--;
    inARow++;
    generateAlienPosition(alien_x, alien_y, player_x, player_y);
    cout <<"The alien's position has been refreshed to a new location." << endl;
  }
  else {
    cout << "Missed! The alien is raging!"<< endl;
    inARow = 0;
    bullets--;
  }
  if(inARow ==2){
    cout <<"Congratulations! You hit the alien twice in a row and received an extra life and additional bullets! ";
    inARow =0;
    bullets += ((rand() % 5) +3); // random number 3-7
    humanLives++;
    cout <<"You now have "<< humanLives << " lives and "<< bullets << " bullets."<< endl;
  }
  return;
}

void acquirePowerUp(point power_x, point power_y, point player_x, point player_y, int & humanLives, int & bullets, int &immunity_duration, string &powerUp){
  cout << "The powerup position is ("<< power_x.m_XCoord << ", " << power_y.m_YCoord << ")" << endl;
   int powerup_type = rand() % 5; //used for 80/20% calculation
  if(power_x.m_XCoord == player_x.m_XCoord && power_y.m_YCoord == player_y.m_YCoord){//if player is in the same spot as the powerup
    if(powerup_type <5){// for non sheild power up
      if(((power_x.m_XCoord + power_y.m_YCoord) % 2) == 0){// even
        humanLives += (power_x.m_XCoord + power_y.m_YCoord);
        cout << "Power up! You aquired additional lives! You now have "<< humanLives << " lives." << endl;
        powerUp ="lives";
        generatePowerUpPosition(power_x, power_y);
        return;
      }else if(((power_x.m_XCoord + power_y.m_YCoord) % 2) == 1){//odd
        bullets += (power_x.m_XCoord + power_y.m_YCoord);
        cout << "Power up! you aquired additional bullets! You now have "<< bullets << " bullets." << endl;
        powerUp ="bullets";
        generatePowerUpPosition(power_x, power_y);
        return;
      }
      generatePowerUpPosition(power_x,power_y);
    }else if(powerup_type ==5){//sheild powerup
      powerUp ="sheild";
      immunity_duration +=2;
      generatePowerUpPosition(power_x, power_y);
      return;
    }
  }
  cout << "You did not acquire the powerup. "<< endl;
  powerUp = "None";
  return;
}

void shootPlayer(point player_last_x, point player_last_y, point alien_x, point alien_y, int &humanLives, int &immunity_duration){
  cout<<"The Alien is attacking you!" << endl;
  if(immunity_duration == 0){ // if no sheild then run alien shoots player
  if(alien_x.m_XCoord == player_last_x.m_XCoord && alien_y.m_YCoord == player_last_y.m_YCoord){
    cout << "You got hit by the alien and lost 2 lives" << endl;
    humanLives -= 2;
    return ;
  }else if((abs(player_last_x.m_XCoord - alien_x.m_XCoord)  == 1 && player_last_y.m_YCoord == alien_y.m_YCoord) || (player_last_x.m_XCoord == alien_x.m_XCoord) && abs(player_last_y.m_YCoord - alien_y.m_YCoord) == 1){
    cout << "The alien was close! You lost 1 life." << endl;
    humanLives -= 1;
    return;
  }else{
  cout << "The alien Missed!"<< endl;
    return;
  }
  }
  cout << "Your sheild protected you from damage." << endl;
  immunity_duration--;
  return;
}

void displayGameStatus(int humanLives, int alienLives, int &bullets, string powerUp, point player_x, point player_y, point alien_x, point alien_y){
  if(bullets > 20){
    bullets = 20;
  }if(humanLives < 0){
    humanLives =0;
  }if(alienLives < 0){
    alienLives =0;
  }
  
  cout <<"Human lives: " << humanLives <<endl;
  cout <<"Alien lives: " << alienLives << endl;
  cout <<"Bullets remaining: "<< bullets << endl;
  cout << "Powerup acquired: "<< powerUp << endl;
  cout << "Play board: "<< endl;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      if (player_x.m_XCoord == j && player_y.m_YCoord == i){
          cout << "P";
      }else if(alien_x.m_XCoord == j && alien_y.m_YCoord == i){
          cout << "A";
      }else{
          cout << "o";
      }
      cout << " ";
    }
    cout << endl;
  }
}