//
// Created by Rob on 11/14/2022.
//


#include <iostream>
#include "Shuffle.h"
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#define SORRY 13
using namespace std;


void Deck::shuffledeck(){ // member function of deck class, it shuffles the deck using the random engine and
    // prints that the deck
    //was shuffled

    shuffle (carddeck.begin(), carddeck.end(), default_random_engine(num));
    cout << "The deck has been shuffled!" <<endl;
}

int Deck::DealCard() { // deal card gives a card to the player, if the end of the deck has been reached, we shuffle the deck
    //and start over
    int give;
    if (DeckPosition == 45) {


        DeckPosition = 0;
        shuffledeck();

        give = DealCard();
        return give;
    }
    else {
        give = carddeck[DeckPosition];
        DeckPosition++;
        return give;
    }

}

int randomPawn(){ // this gives me a random pawn 1-4 for computer AI

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 4); // define the range

    return distr(gen);
}



