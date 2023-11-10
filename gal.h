#ifndef GAL_H
#define GAL_H
#include <string>
using namespace std;
struct point{
  int m_XCoord;
  int m_YCoord;
};
//Function to generate a position for the player 0-3 at random
//Pre: none
//Post: randomizes players position with x and y coordinates
void generatePlayerPosition(point & player_x, point &player_y);

//Function to generate a position for the alien 0-3 at random
//Pre: none
//Post: randomizes aliens position with x and y coordinates
void generateAlienPosition(point & alien_x, point &alien_y);

///Function to generate a position for the powerup 0-3 at random
//Pre: none
//Post: randomizes powerups position with x and y coordinates 
void generatePowerUpPosition(point & power_x, point &power_y);

//Function that takes in the user's (x,y)coordinate guess and damages the alien if they match the coordinate of the alien
//Pre: must have alien position
//Post: subtracts lives if the player correctly guesses the position or is close to the position and updates bullets
void shootAlien(point guess_x, point guess_y, point alien_x, point alien_y, int &alienLives, int &bullets, int &humanLives);

//function used to generated type of powerup and to check if the player is in the same coordinate to give the player the powerup
//Pre: coordinate of the powerup (x,y) //power_x/y
//Post: adds lives, bullets, or immunity_duration for the corresponding powerup if player coordinates match
void acquirePowerUp(point power_x, point power_y, point player_x, point player_y, int & humanLives, int & bullets, int & immunity_duration, string &powerUp);

//Fuction that lets the alien damage the player based on if the alien moves to the players previous position
//Pre: player_last_x/y // must have the last position of the player and cannot run on the first round
//Post: subtracts lives from human if the alien moves to or close to the players previous position
void shootPlayer(point player_x, point player_y, point alien_x, point alien_y, int &humanLives, int &immunity_duration);

//function that outputs current values for human lives, alien lives, and bullets
//Pre: none
//Post: outputs remaining human and alien lives and bullets
void displayGameStatus(int humanLives, int alienLives, int &bullets, string powerUp, point player_x, point player_y, point alien_x, point alien_y);

#endif