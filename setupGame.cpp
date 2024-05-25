#include "GameObjects.h"
#include "Shuffle.h"
#include "setupGame.h"
#include <iostream>
#include <string>

using namespace std;


void setUser(Player* Player1, Player* Player2,Player* Player3, Player* Player4, string inputColor){
    //this function takes in all of the players and assigns them a color based on the human players choice
    // it also calls set pawns to initialize the pawns
    if (inputColor == "Red" || inputColor == "red"){ // if input color is red, the human player is red
      Player1->color = "red";
      Player2->color = "blue";
      Player3->color = "yellow";
      Player4->color = "green";
      setPawns(Player1);
      setPawns(Player2);
      setPawns(Player3);
      setPawns(Player4);
      cout << "You are Player 1 and your color is red." << endl;
      return;
    }
    if (inputColor == "Blue" || inputColor == "blue"){// if input color is blue, the human player is blue
      Player1->color = "blue";
      Player2->color = "red";
      Player3->color = "yellow";
      Player4->color = "green";
      setPawns(Player1);
      setPawns(Player2);
      setPawns(Player3);
      setPawns(Player4);
      cout << "You are Player 1 and your color is blue." << endl;
      return;
    }
    if (inputColor == "Yellow" || inputColor == "yellow"){// if input color is yellow, human player is yellow
      Player1->color = "yellow";
      Player2->color = "blue";
      Player3->color = "red";
      Player4->color = "green";
      setPawns(Player1);
      setPawns(Player2);
      setPawns(Player3);
      setPawns(Player4);
      cout << "You are Player 1 and your color is yellow." << endl;
      return;
    }
    if (inputColor == "Green" || inputColor == "green"){// if input color is green, the human player is green
      Player1->color = "green";
      Player2->color = "blue";
      Player3->color = "yellow";
      Player4->color = "red";
      setPawns(Player1);
      setPawns(Player2);
      setPawns(Player3);
      setPawns(Player4);
      cout << "You are Player 1 and your color is green." << endl;
      return;
    }
    else{
      cout<<"Invalid try again" << endl;
      cout << "What color would you like to be? 'red', 'yellow', 'blue', or 'green'" << endl;
      cin >> inputColor;
      setUser(Player1, Player2,Player3, Player4, inputColor); // if the player puts in an invalid color, it calls the
      //function again
    }
}


void setPawns(Player* P){
    //this function initializes the players pawn locations and color
    int startLocation,homeLocation, safetyZoneLocation;
    if(P->color == "red"){
        startLocation = 4;
        homeLocation = 2;
        safetyZoneLocation = 60;
        for(int i = 0; i < 4; i++){
            P->piece[i].color = "red";
            P->piece[i].StartLocation = startLocation;
            P->piece[i].HomeLocation = homeLocation;
            P->piece[i].SafetyZoneLocation = safetyZoneLocation;
        }
    }
    if(P->color == "blue"){
        startLocation = 19;
        homeLocation = 17; //each color has a unique home, start, and safety location on the board
        safetyZoneLocation = 66;
        for(int i = 0; i < 4; i++){
            P->piece[i].color = "blue";
            P->piece[i].StartLocation = startLocation;
            P->piece[i].HomeLocation = homeLocation;
            P->piece[i].SafetyZoneLocation = safetyZoneLocation;
        }
    }
    if(P->color == "yellow"){
        startLocation = 34;
        homeLocation = 32;
        safetyZoneLocation = 72;
        for(int i = 0; i < 4; i++){
            P->piece[i].color = "yellow";
            P->piece[i].StartLocation = startLocation;
            P->piece[i].HomeLocation = homeLocation;
            P->piece[i].SafetyZoneLocation = safetyZoneLocation;
        }
    }
    if(P->color == "green"){
        startLocation = 49;
        homeLocation = 47;
        safetyZoneLocation = 78;
        for(int i = 0; i < 4; i++){
            P->piece[i].color = "green";
            P->piece[i].StartLocation = startLocation;
            P->piece[i].HomeLocation = homeLocation;
            P->piece[i].SafetyZoneLocation = safetyZoneLocation;
        }
    }
}

void printLocation(Player* active){
    //takes in the active player and prints out the proper locations
    int printL;
    for (int i = 0; i < 4; i++){
        if (active->piece[i].Start){ //if the player is in start, it says its in start
            cout << "Piece " << i + 1 << " is at Start." << endl;
        }
        else if(active->piece[i].SafetyZone){ // if its in safety zone, it states its a certain position away from home
            cout << "Piece " << i + 1 << " is " << (active->piece[i].SafetyZoneLocation + 5) - (active->piece[i].location) << " space(s) away from Home." << endl;
        }
        else if(active->piece[i].Home){ // if its in home it will tell the user its at home
            cout << "Piece " << i + 1 << " is at Home." << endl;
        }
        else {// it will show the location on the board and hpw many spaces away from home
            if(active->piece[i].location > active->piece[i].HomeLocation){
                printL = (60 - active->piece[i].location) + active->piece[i].HomeLocation;
            }else{
                printL = (active->piece[i].HomeLocation - active->piece[i].location);
            }

            cout << "Piece " << i + 1 << " is at location " << active->piece[i].location << " and is "<< printL << " space(s) away from the safety zone." << endl;
        }
    }
}

int CheckBoard(Player* check, GameBoard *Board, int Pawn, int Card){
//main check function that is called for every move, check players movement to see if its valid
    int tempMove;
    int tempLocation = check->piece[Pawn].location;
tempMove = Card;
    int moveMessage = Card;

    string outputColor = check->color;
    for(char &c: outputColor)
        c = c & ~' ';


    if(tempMove == 0){ //  going out of start space and checking that location
        tempLocation = check->piece[Pawn].StartLocation;    //if the space out of start is not occupied, moves pawn to
        //beginning location
        if(!Board->SorryBoard[tempLocation].occupied){
            Board->SorryBoard[tempLocation].occupied = true;
            check->piece[Pawn].Start = false;
            Board->SorryBoard[tempLocation].playeronspace = &check->piece[Pawn];
            return tempLocation;
        }
        else{
            //if a pawn is on that location, it sends it back
            cout << Board->SorryBoard[tempLocation].playeronspace->color <<"'s pawn has been sent back to home!" << endl ;
            Board->SorryBoard[check->piece[Pawn].location].occupied = false;
            Board->SorryBoard[tempLocation].playeronspace->location = Board->SorryBoard[tempLocation].playeronspace->StartLocation;
            Board->SorryBoard[tempLocation].playeronspace->Start = true;
            Board->SorryBoard[tempLocation].playeronspace = &check->piece[Pawn];
            return tempLocation;
            // move pawn currently on the space back to its start location and replace current player into current location
        }

    }
    while(tempMove > 0 || tempMove < 0){ // while loop for card movement
        if(tempMove > 0) { //if its a forward card, it increments location and decrements the card
            tempLocation++;
            tempMove--;
        }
        else{
            tempLocation--; //if its a backwards card, it increments location and decrements the card
            tempMove++;
        }
        if(tempLocation == 60 && !check->piece[Pawn].SafetyZone){ //
            tempLocation = 0; //loop around board forwards
    }
        if(tempLocation == -1){ // loop around board backwards
            tempLocation = 59;
        }

        if(check->piece[Pawn].HomeLocation == tempLocation || check->piece[Pawn].SafetyZone){
            //if the piece is about to move into the safety zone or is in the safety zone it goes through this check
            if(!check->piece[Pawn].SafetyZone) { // it sets it in safety zone if it wasnt in it before
                tempLocation = check->piece[Pawn].SafetyZoneLocation;
                if(tempMove<0){ // if its going backwards into it, then it flips the card movement to go forward
                    tempMove= tempMove * -1;
                }
            }
            if((tempLocation + tempMove) > (check->piece[Pawn].SafetyZoneLocation + 5)){
                //if movement is greater than safety zone, lose turn
                cout << "Too far of a move. You lose your turn" << endl;
                return check->piece[Pawn].location; // piece moved too far past safety zone, loses turn and same position is returned.
             }
            else if((tempLocation + tempMove) == (check->piece[Pawn].SafetyZoneLocation + 5)){
                //if its exact, it moves into home and sets its home state to true
                cout << "You have moved pawn " << Pawn + 1 << " into your home. Congrats!" << endl;
                check->piece[Pawn].Home = true;
                check->piece[Pawn].Start = false;
                check->piece[Pawn].SafetyZone = false;
                Board->SorryBoard[check->piece[Pawn].location].occupied = false;
                return check->piece[Pawn].SafetyZoneLocation + 5;
            }
            else if(Board->SorryBoard[tempLocation + tempMove].occupied){
                //if the space in the safety zone is occupied, lose turn
                cout << " That space is already occupied. You lose your turn." << endl;
                return check->piece[Pawn].location;
            }
            else{
                Board->SorryBoard[check->piece[Pawn].location].occupied = false;
                check->piece[Pawn].SafetyZone = true;
                Board->SorryBoard[tempLocation + tempMove].occupied = true;
                cout <<  "Your pawn is in the safety zone and is " << ((check->piece[Pawn].SafetyZoneLocation + 5) - (tempLocation + tempMove)) << " spaces away from home." << endl;
                return tempLocation + tempMove;
                //else it moves the pawn into safety zone normally
            }

            }
    }


    if(!Board->SorryBoard[tempLocation].occupied){//if its still moving on the board and space is not occupied,
        //it moves the pawn normally
        Board->SorryBoard[check->piece[Pawn].location].occupied = false;
        Board->SorryBoard[tempLocation].occupied = true;
        Board->SorryBoard[tempLocation].playeronspace = &check->piece[Pawn];
        if(check->Human){
            cout << "Your pawn has moved " << moveMessage << " space(s)." << endl;
        }
        else{
            cout << outputColor <<"'s pawn has moved " << moveMessage << " space(s). " << endl;
        }
        return tempLocation;
    }
    else if(Board->SorryBoard[tempLocation].occupied && Board->SorryBoard[tempLocation].playeronspace->color == check->color){
        //if the pawn is moved onto a space of its own color , you lose your turn
        cout<< "You cannot move your pawn onto a space already occupied by your own color." << endl;
        cout<< "You lose your turn." << endl;
        return check->piece[Pawn].location;
    }
    else{
        //otherwise the space is occupied and it sends it back home
        outputColor = Board->SorryBoard[tempLocation].playeronspace->color;
        for(char &c: outputColor)
            c = c & ~' ';
        cout <<outputColor <<"'s pawn has been sent back to home!" << endl ;
        Board->SorryBoard[check->piece[Pawn].location].occupied = false;
        Board->SorryBoard[tempLocation].playeronspace->location = Board->SorryBoard[tempLocation].playeronspace->StartLocation;
        Board->SorryBoard[tempLocation].playeronspace->Start = true;
        Board->SorryBoard[tempLocation].playeronspace = &check->piece[Pawn];
        // move pawn currently on the space back to its start location and replace current player into current location
    }
    if (Board->SorryBoard[tempLocation].color != check->color &&
            Board->SorryBoard[tempLocation].type == 'l' ){
        //LONG SLIDE, checks the next 5 locations and slides the pawn, sending other pawns back if needed
        Board->SorryBoard[check->piece[Pawn].location].occupied = false;
        Board->SorryBoard[tempLocation].occupied = false;
        for(int i = 1; i < 6; i++){ // goes through loop to check next spaces
            if(Board->SorryBoard[tempLocation + i].occupied){//sends pawns back home if they are in the slide
                outputColor = Board->SorryBoard[tempLocation].playeronspace->color;
                for(char &c: outputColor)
                    c = c & ~' ';
                cout << outputColor <<"'s pawn has been sent back to home!" << endl ;
                Board->SorryBoard[tempLocation + i].playeronspace->location = Board->SorryBoard[tempLocation].playeronspace->StartLocation;
                Board->SorryBoard[tempLocation + i].occupied = false;
            }
        }
        tempLocation += 5;
        Board->SorryBoard[tempLocation].occupied = true;
        Board->SorryBoard[tempLocation].playeronspace = &check->piece[Pawn]; // adds slide spaces to final destination
        if(check->Human){
            cout << "Your pawn has moved " << moveMessage + 5<< " space(s)." << endl;
        }
        else{
            outputColor = check->color;
            for(char &c: outputColor)
                c = c & ~' ';
            cout << outputColor <<"'s pawn has moved " << moveMessage + 5<< " spaces " << endl;
        }

        return tempLocation;
    }
    if (Board->SorryBoard[tempLocation].color != check->color &&
        Board->SorryBoard[tempLocation].type == 's' ){
        //SHORT SLIDE, checks the next 5 locations and slides the pawn, sending other pawns back if needed
        Board->SorryBoard[check->piece[Pawn].location].occupied = false;
        Board->SorryBoard[tempLocation].occupied = false;
        for(int i = 1; i < 5; i++){// goes through loop to check next spaces
            if(Board->SorryBoard[tempLocation + i].occupied){//sends pawns back home if they are in the slide
                outputColor = Board->SorryBoard[tempLocation].playeronspace->color;
                for(char &c: outputColor)
                    c = c & ~' ';
                cout << outputColor <<"'s pawn has been sent back to home!" << endl ;
                Board->SorryBoard[tempLocation + i].playeronspace->location = Board->SorryBoard[tempLocation].playeronspace->StartLocation;
                Board->SorryBoard[tempLocation + i].occupied = false;
            }
        }
        tempLocation += 4;
        Board->SorryBoard[tempLocation].occupied = true;// adds slide spaces to final destination
        Board->SorryBoard[tempLocation].playeronspace = &check->piece[Pawn];
        if(check->Human){
            cout << "Your pawn has moved " << moveMessage + 4<< " spaces." << endl;
        }
        else{
            outputColor = check->color;
            for(char &c: outputColor)
                c = c & ~' ';
            cout << outputColor <<"'s pawn has moved " << moveMessage + 4 << " spaces " << endl;
        }
        return tempLocation;

    }
    if(check->Human){
        cout << "Your pawn has moved " << moveMessage << " spaces." << endl;
    }
    else{
        outputColor = check->color;
        for(char &c: outputColor)
            c = c & ~' ';
        cout << outputColor <<"'s pawn has moved " << moveMessage << " spaces " << endl;
    }
    return tempLocation;
}