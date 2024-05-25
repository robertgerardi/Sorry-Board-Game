//
// Created by Rob on 12/7/2022.
//

#ifndef INC_309_FINAL_PROJECT_SHUFFLE_H
#define INC_309_FINAL_PROJECT_SHUFFLE_H


#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#define SORRY 13
using namespace std;

class Deck{ // this class makes a vector with the cards inside
public:
    int DeckPosition = 0;
    array<int,45> carddeck{1,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,7,7,7,7,8,8,8,8,10,10,10,10,11,11,11,11,12,12,12,12,SORRY,SORRY,SORRY,SORRY};
    unsigned num = chrono::system_clock::now().time_since_epoch().count();

    Deck(){};
    void shuffledeck(void); // initialize shuffleDeck to shuffle the deck once we run out of cards
    int DealCard (void);    // deal cards returns a card to the player

};

int randomPawn(void);

#endif //INC_309_FINAL_PROJECT_SHUFFLE_H
