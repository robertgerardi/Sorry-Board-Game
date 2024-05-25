//
// Created by Rob on 12/11/2022.
//

#ifndef INC_309_FINAL_PROJECT_GAMEOBJECTS_H
#define INC_309_FINAL_PROJECT_GAMEOBJECTS_H



#include <string>
#include "Shuffle.h"
#include <iostream>
#include <string>

using namespace std;



class Pawn{
public:
    string color; //pawn color
    bool Start; //pawn start bool
    bool Home; // pawn home bool
    bool SafetyZone; // pawn safety zone bool
    int location; // pawns location on board
    int HomeLocation;// pawns home location for referencing
    int StartLocation;// pawns start location for referencing
    int SafetyZoneLocation;// pawns safety zone location for referencing

    Pawn(){Start = true; Home = false; SafetyZone = false; location = 0;}

};

class BoardSpace{ //each board space on the board

public:
    char type; // each board space has a type like long slide or normal slide
    string color; // each space has a color if it slides
    bool occupied; // occupied bool
    Pawn * playeronspace; // pointer to pawn on space

    BoardSpace(){type = ' '; color = ' '; occupied = false;}

};


class GameBoard {

public:
    BoardSpace SorryBoard[84]; //sorryboard with 84 spots

    GameBoard(){ createboard();}
    void createboard(); //creates the board in the orientation RBYG

};

class Player{
public:
    Pawn piece [4]; // each player has 4 pawns
    string color; // each player has a color
    bool Human; // player has a boolean for human
    Player() { color = ' ';}
    Player(string setcolor){color = setcolor;}



    virtual void PlayGame( bool GameOver, int Card, GameBoard *Board, Deck SorryDeck) = 0;
    //virtual function to be overrided by the human and computer player classes

};



class HumanPlayer : public Player {
public://human player inherits from player

    HumanPlayer(){color = "";Human = true;}
    HumanPlayer(string input) { color = input;}

    void PlayGame( bool GameOver, int Card, GameBoard *Board, Deck SorryDeck) override;
    //play game is overridden and specific to human player
};


class ComputerPlayer : public Player {
public:// computer player inherits from player

    ComputerPlayer(){color = ""; Human = false;}
    ComputerPlayer(string input) { color = input; Human = false;}

    void PlayGame( bool GameOver, int Card, GameBoard *Board, Deck SorryDeck) override;
    //play game is overridden and specific to computer player
};

// we originally had these as virtual but we had to change them after having difficulties with pointers
void Play11or13Human(Player* active,int Card, GameBoard *Board, Player* ComputerPlayer2,Player* ComputerPlayer3,Player* ComputerPlayer4);
void Play11or13Computer(Player* active,int Card, GameBoard *Board, Player* ComputerPlayer2,Player* ComputerPlayer3,Player* ComputerPlayer4);
#endif //INC_309_FINAL_PROJECT_GAMEOBJECTS_H
