//
// Created by Rob on 12/7/2022.
//

#ifndef INC_309_FINAL_PROJECT_SETUPGAME_H
#define INC_309_FINAL_PROJECT_SETUPGAME_H
#include "GameObjects.h"

#include "Shuffle.h"
#include <iostream>
#include <string>
using namespace std;



void setUser(Player* Player1, Player* Player2,Player* Player3, Player* Player4, string inputColor);
//set user sets the colors and pawns for a human player game
void setPawns(Player* P);
//set pawns sets the pawns to their correct locations and assigns the correct values based on color
void printLocation(Player* active);
//print location prints out the locations of all the pieces for the active player
int CheckBoard(Player* active, GameBoard *Board, int a, int Card);
//check board is the main check function for moving pawns on the board
#endif //INC_309_FINAL_PROJECT_SETUPGAME_H
