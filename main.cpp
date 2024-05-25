//
// Created by Rob on 12/6/2022.
//

#include "GameObjects.h"
#include "Shuffle.h"
#include "setupGame.h"

#include <iostream>
#include <string>


int main(void){
    bool GameOver = false; // final game over boolean



cout << "Welcome to Sorry!" << endl;
cout << "This game will be played with 4 players" << endl; //introduces the player to the game
cout << "Would you like to particpate? Y or N" << endl;

char playerchoice;
    while (!(cin >> playerchoice) || ((playerchoice != 'N') && (playerchoice != 'n') && (playerchoice != 'Y') && (playerchoice != 'y'))) {
        cin.clear(); //clear bad input flag
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        cout << "Invalid input; please re-enter.\n";
    }
    // this gets the choice from the player to see if they want to play

Player *playerTurn[4]; // an array with all of the players for easy access

if(playerchoice == 'Y'|| playerchoice == 'y'){
  string inputColor;
  cout << "What color would you like to be? 'red', 'yellow', 'blue', or 'green'" << endl; // if the user wants to play, it allows them to choose their color
    while (!(cin >> inputColor) || ((inputColor != "red") && (inputColor != "yellow") && (inputColor != "blue") && (inputColor != "green"))) {
        cin.clear(); //clear bad input flag
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        cout << "Invalid input; please re-enter.\n";
    }

  cout << endl;

  playerTurn[0] = new HumanPlayer;

  playerTurn[1] = new ComputerPlayer; // this assigns the array of players to the correct players

  playerTurn[2] = new ComputerPlayer;

  playerTurn[3] = new ComputerPlayer;
  setUser(playerTurn[0],playerTurn[1],playerTurn[2],playerTurn[3],inputColor);
  //setuser assigns all the players the proper colors and locations on the board for checking
}
else {
  playerTurn[0] = new ComputerPlayer("red");
    setPawns(playerTurn[0]);

  playerTurn[1] = new ComputerPlayer("green");  // if a human player is not created, then the game is
    setPawns(playerTurn[1]);

  playerTurn[2] = new ComputerPlayer("yellow");
    setPawns(playerTurn[2]);

  playerTurn[3] = new ComputerPlayer("blue");
    setPawns(playerTurn[3]);
}




GameBoard SorryBoard; //gameboard is created
Deck SorryDeck;// deck is created
SorryDeck.shuffledeck(); // deck is shuffled
int ActiveCard;
    while (GameOver == false){// game over state, game runs till someone wins
        for (int i = 0; i < 4; i++){//runs through all four players
            string output = playerTurn[i]->color;
            for(char &c: output)
                c = c & ~' ';
            cout << endl;
            cout << "___________________________________________________________________________________________________" << endl;
            cout << "It is " << output << " players turn" << endl;
            if((playerchoice == 'y' || playerchoice == 'Y') && i == 0) {
                    char drawinput = '\0';
                    cout << "Type any character and press Enter to draw a card" << endl; // makes player type input
                    //to draw card
                    cin >> drawinput;
                    cout << endl;
                    if (drawinput != '\0') {
                        ActiveCard = SorryDeck.DealCard();
                    }
                if (ActiveCard == 11 || ActiveCard == 13){ //11 and 13 have special swap function to be called
                    Player* inactivePlayer[3];
                    int j = 0;
                    for (int k = 0; k < 4; k++) {
                        if (playerTurn[i] != playerTurn[k]) {
                            inactivePlayer[j] = playerTurn[k]; // checks through available players that are not the active
                            j++;
                        }
                    }
                    Play11or13Human(playerTurn[i],ActiveCard, &SorryBoard, inactivePlayer[0], inactivePlayer[1], inactivePlayer[2]);
                    //calls 11 or 13 function for human, if the players is human
                }
                else{
                    playerTurn[i]->PlayGame(GameOver, ActiveCard, &SorryBoard, SorryDeck);
                    //plays normal game if its any other card
                }
            }
            else {
                ActiveCard = SorryDeck.DealCard(); // does the same thing for computer player
                if (ActiveCard == 11 || ActiveCard == 13){
                    Player* inactivePlayer[3];
                    int j = 0;
                    for (int k = 0; k < 4; k++) {
                        if (playerTurn[i] != playerTurn[k]) {
                            inactivePlayer[j] = playerTurn[k];
                            j++;
                        }
                    }
                    Play11or13Computer(playerTurn[i],ActiveCard, &SorryBoard, inactivePlayer[0], inactivePlayer[1], inactivePlayer[2]);
                    //calls computer player function for 11 or 13
                }
                else{
                    playerTurn[i]->PlayGame(GameOver, ActiveCard, &SorryBoard, SorryDeck);
                    //players regular card for computer player using override
                }
            }


            if (playerTurn[i]->piece[0].Home && playerTurn[i]->piece[1].Home && playerTurn[i]->piece[2].Home && playerTurn[i]->piece[3].Home){
                GameOver = true; // checks home state, stops loop and displays winner
                string outputColor = playerTurn[i]->color;
                for (char &c: outputColor) {
                    c = c & ~' ';
                }
                cout << outputColor << " has won the game of Sorry!" << endl;
                i = 4;
            }
        }
    }
    return 0;
}
