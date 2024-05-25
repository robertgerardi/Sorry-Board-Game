//
// Created by Rob on 12/11/2022.
//

#include "GameObjects.h"
#include "setupGame.h"

void HumanPlayer::PlayGame(bool GameOver,int Card,GameBoard *Board, Deck SorryDeck) { // This function is how the game plays for the HumanPlayer.
    if (Card != 2) { // since PlayGame is recursively called it will not print a repeat of the pieces
        printLocation(this); // call again after case statement
    }
    cout << endl;
    string outputColor = this->color; // assigns the color of the current to a variable
    for (char &c: outputColor) { // makes the color all uppercase to help for readability
        c = c & ~' ';
    }
    cout << outputColor << " has drawn the " << Card << " card." << endl; // outputs the card drawn to screen
    int PawnChosen;
    char PlayerChoice;
    int PieceChoice;
    int SpacestoMove;
    int counter = 0;
    int tempCard = 0;
    char Choice;
    switch (Card) { // switch-case statement that checks for each card and how it will apply to a piece
        case 1:
            if((Board->SorryBoard[this->piece[0].StartLocation].occupied) && (this->color == Board->SorryBoard[this->piece[0].StartLocation].playeronspace->color)){ // defaults to moving a piece one space forward because your start space is currently occupied by your own color.
                Choice = 'n';
                cout << "You cannot move a pawn out of start onto an occupied space of your own color." << endl;
            }
            else if (this->piece[0].Start && this->piece[1].Start && this->piece[2].Start && // if all pieces are in Start, it defaults to moving a piece out of start.
                     this->piece[3].Start){
                Choice = 'y';
            }
            else{
                cout << "Type Y (if you want to move a piece out of Home). Type N (to move an existing piece one space forward)" << endl; // player can choose what they want to do
                while (!(cin >> Choice) || ((Choice != 'N') && (Choice != 'n') && (Choice != 'Y') && (Choice != 'y'))) { // keeps on looping until player puts in a valid input (failsafe).
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
            }

            if ((this->piece[0].Start || this->piece[1].Start || this->piece[2].Start || // if at least one player is out of start and the player chooses to move a player out of start, then it starts prompting accordingly.
                 this->piece[3].Start) && (Choice == 'Y' || Choice == 'y')) {
                cout << "Pick a piece to move out of your starting location" << endl;
                cout << "1, 2, 3, or 4" << endl;
                while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                       (!this->piece[PawnChosen - 1].Start) || this->piece[PawnChosen - 1].Home) { //keeps on looping until player puts in a valid input (failsafe).
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                cout << "You have chosen piece " << PawnChosen << ". It has been moved out of the starting location."
                     << endl;

                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, 0); // calls CheckBoard to update spaces on the board

            }
            if ((!this->piece[0].Start || !this->piece[1].Start || !this->piece[2].Start || // checks to see if at least one player is not in start.
                 !this->piece[3].Start) && (Choice == 'N' || Choice == 'n')) {
                cout << "Pick a piece to move" << endl;
                cout << "1, 2, 3, or 4" << endl;
                while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) || //keeps on looping until player puts in a valid input (failsafe).
                       this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) {
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // calls CheckBoard to update spaces on the board
            }
            break;
        case 2:
            if((Board->SorryBoard[this->piece[0].StartLocation].occupied) && (this->color == Board->SorryBoard[this->piece[0].StartLocation].playeronspace->color)){ // defaults to moving a piece one space forward because your start space is currently occupied by your own color.
                Choice = 'n';
                cout << "You cannot move a pawn out of start onto an occupied space of your own color." << endl;
            }
            else if (this->piece[0].Start && this->piece[1].Start && this->piece[2].Start && // automatically makes the user move a piece out of Start if all pieces are in Start.
                     this->piece[3].Start){
                Choice = 'y';
            }
            else{
                cout << "Type Y (if you want to move a piece out of Start). Type N (to move an existing piece two spaces forward)" << endl;
                while (!(cin >> Choice) || ((Choice != 'N') && (Choice != 'n') && (Choice != 'Y') && (Choice != 'y'))) { //keeps on looping until player puts in a valid input (failsafe).
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
            }

            if ((this->piece[0].Start || this->piece[1].Start || this->piece[2].Start ||
                 this->piece[3].Start) && (Choice == 'Y' || Choice == 'y')) { // Move a piece out of start location
                cout << "Pick a piece to move out of your starting location" << endl;
                cout << "1, 2, 3, or 4" << endl;
                while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                       (!this->piece[PawnChosen - 1].Start) || this->piece[PawnChosen - 1].Home) { //keeps on looping until player puts in a valid input (failsafe).
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                cout << "You have chosen piece " << PawnChosen << ". It has been moved out of the starting location."
                     << endl;

                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, 0); // calls CheckBoard to update spaces on the board
                char drawinput = '\0';
                cout << "You have earned another turn! Type a character and press Enter to draw a card" << endl;
                cin >> drawinput;
                if (drawinput != '\0') {
                    tempCard = SorryDeck.DealCard();
                }
                //SorryDeck.DealCard();
                PlayGame(GameOver, tempCard, Board, SorryDeck);
                // Draw Card Again then call function again;
            }
            if ((this->piece[0].Start || this->piece[1].Start || this->piece[2].Start ||
                 this->piece[3].Start) && (Choice == 'N' || Choice == 'n')) { // Move a piece two spaces forward.
                cout << "Pick a piece to move" << endl;
                cout << "1, 2, 3, or 4" << endl;
                while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                       this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) { //keeps on looping until player puts in a valid input (failsafe).
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // calls CheckBoard to update spaces on the board
            }
            break;
        case 3:
            counter = 0;
            for (int i = 0; i < 4; i++){
                if (this->piece[i].Start || this->piece[i].Home){ // checks to see if all pieces are in Start or Home,
                    counter++;
                }
            }
            if (counter == 4) {
                cout << "There are no pieces that you can move." << endl;
                return;
            }
            if (!this->piece[0].Start || !this->piece[1].Start || !this->piece[2].Start || // move piece 3 spaces forward.
                !this->piece[3].Start) {
                cout << "Pick a piece to move" << endl;
                cout << "1, 2, 3, or 4" << endl;
                while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                       this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) { //keeps on looping until player puts in a valid input (failsafe).
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // calls CheckBoard to update spaces on the board
            }
            break;
        case 4:
            counter = 0;
            for (int i = 0; i < 4; i++){
                if (this->piece[i].Start || this->piece[i].Home){ // checks to see if all pieces are in Start or Home,
                    counter++;
                }
            }
            if (counter == 4) {
                cout << "There are no pieces that you can move." << endl;
                return;
            }
            if (!this->piece[0].Start || !this->piece[1].Start || !this->piece[2].Start ||
                !this->piece[3].Start) { // move a piece four spaces backward
                cout << "Pick a piece to move" << endl;
                cout << "1, 2, 3, or 4" << endl;
                while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                       this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) { // failsafe
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, -Card); // calls CheckBoard to update spaces on the board
            }
            else{
                cout << "None of your pieces are out of Start. You lose your turn." << endl;
            }
            break;
        case 5:
            counter = 0;
            for (int i = 0; i < 4; i++){
                if (this->piece[i].Start || this->piece[i].Home){ // checks to see if all pieces are in Start or Home,
                    counter++;
                }
            }
            if (counter == 4) {
                cout << "There are no pieces that you can move." << endl;
                return;
            }
            if (!this->piece[0].Start || !this->piece[1].Start || !this->piece[2].Start ||
                !this->piece[3].Start) { // moves a piece five spaces forward
                cout << "Pick a piece to move" << endl;
                cout << "1, 2, 3, or 4" << endl;
                while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                       this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) { // failsafe
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // calls CheckBoard to update spaces on the board
            }
            break;
        case 7:
            counter = 0;
            for (int i = 0; i < 4; i++){
                if (this->piece[i].Start || this->piece[i].Home){ // checks to see if all pieces are in Start or Home,
                    counter++;
                }
            }
            if (counter == 4) {
                cout << "There are no pieces that you can move." << endl;
                return;
            }

            if (!this->piece[0].Start || !this->piece[1].Start || !this->piece[2].Start ||
                !this->piece[3].Start) { // User choice of moving forward 7 spaces or splitting the spaces between pawns.
                cout << "Type Y (Do you want to move one pawn 7 spaces forward?) or Type N (Do you want to split the number of spaces you move to two pawns?)" << endl;
                while (!(cin >> Choice) || ((Choice != 'N') && (Choice != 'n') && (Choice != 'Y') && (Choice != 'y'))) { // failsafe
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                if (Choice == 'Y' || Choice == 'y') { // moving 7 spaces forward case
                    cout << "Pick a piece to move" << endl;
                    cout << "1, 2, 3, or 4" << endl;
                    while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                           this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) { // failsafe
                        cin.clear(); //clear bad input flag
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                        cout << "Invalid input; please re-enter.\n";
                    }
                    this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // calls CheckBoard to update spaces on the board
                }
                if ((Choice == 'N' || Choice == 'n')) { // splitting the pawns case
                    cout << "What is the first piece you want to move?" << endl;
                    while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                           this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) { // failsafe
                        cin.clear(); //clear bad input flag
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                        cout << "Invalid input; please re-enter.\n";
                    }
                    cout << "How many spaces do you want to move with this piece?" << endl;
                    while (!(cin >> SpacestoMove) || ((Card - SpacestoMove) < 0) ||
                           this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) { // failsafe
                        cin.clear(); //clear bad input flag
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                        cout << "Invalid input; please re-enter.\n";
                    }
                    this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1,SpacestoMove); // calls CheckBoard to update spaces on the board
                    cout << "Piece " << PawnChosen << "has been moved " << SpacestoMove << " space(s)." << endl;
                    SpacestoMove = Card - SpacestoMove; // finds the amount left that the user can move
                    cout << "What is the next piece do you want to move?" << endl;
                    while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                           this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home ) { // failsafe
                        cin.clear(); //clear bad input flag
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                        cout << "Invalid input; please re-enter.\n";
                    }
                    this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1,SpacestoMove); // calls CheckBoard to update spaces on the board
                    cout << "Piece " << PawnChosen << "has been moved " << SpacestoMove << " space(s)." << endl;
                }
            }
            break;
        case 8:
            counter = 0;
            for (int i = 0; i < 4; i++){
                if (this->piece[i].Start || this->piece[i].Home){ // checks to see if all pieces are in Start or Home,
                    counter++;
                }
            }
            if (counter == 4) {
                cout << "There are no pieces that you can move." << endl;
                return;
            }
            if (!this->piece[0].Start || !this->piece[1].Start || !this->piece[2].Start ||
                !this->piece[3].Start) { // move piece 8 spaces forward
                cout << "Pick a piece to move" << endl;
                cout << "1, 2, 3, or 4" << endl;
                while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                       this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) { // failsafe
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // calls CheckBoard to update spaces on the board
            }
            break;
        case 10:
            counter = 0;
            for (int i = 0; i < 4; i++){
                if (this->piece[i].Start || this->piece[i].Home){ // checks to see if all pieces are in Start or Home,
                    counter++;
                }
            }
            if (counter == 4) {
                cout << "There are no pieces that you can move." << endl;
                return;
            }
            if (!this->piece[0].Start || !this->piece[1].Start || !this->piece[2].Start ||
                !this->piece[3].Start) { // choice between moving 10 spaces forward or 1 space backward
                cout << "Type Y (to move 10 spaces forward). Type N (to move 1 space backward)" << endl;
                while (!(cin >> Choice) || ((Choice != 'N') && (Choice != 'n') && (Choice != 'Y') && (Choice != 'y'))) { // failsafe
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                if ((Choice == 'Y' || Choice == 'y')) { // move 10 spaces forward
                    cout << "Pick a piece to move" << endl;
                    cout << "1, 2, 3, or 4" << endl;
                    while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                           this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) { // failsafe
                        cin.clear(); //clear bad input flag
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                        cout << "Invalid input; please re-enter.\n";
                    }
                    this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // calls CheckBoard to update spaces on the board
                }
                if ((Choice == 'N' || Choice == 'n')) { // moving 1 space backward
                    cout << "Pick a piece to move" << endl;
                    cout << "1, 2, 3, or 4" << endl;
                    while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                           this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) { // failsafe
                        cin.clear(); //clear bad input flag
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                        cout << "Invalid input; please re-enter.\n";
                    }
                    this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, -1); // calls CheckBoard to update spaces on the board
                }
            }
            break;
        case 12:
            counter = 0;
            for (int i = 0; i < 4; i++){
                if (this->piece[i].Start || this->piece[i].Home){ // checks to see if all pieces are in Start or Home,
                    counter++;
                }
            }
            if (counter == 4) {
                cout << "There are no pieces that you can move." << endl;
                return;
            }
            if (!this->piece[0].Start || !this->piece[1].Start || !this->piece[2].Start ||
                !this->piece[3].Start) { // moving 12 spaces forward
                cout << "Pick a piece to move" << endl;
                cout << "1, 2, 3, or 4" << endl;
                while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                       this->piece[PawnChosen - 1].Start || this->piece[PawnChosen - 1].Home) { // failsafe
                    cin.clear(); //clear bad input flag
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // calls CheckBoard to update spaces on the board
            }

            break;
        default:break;
    }
    cout << endl;
    printLocation(this);
}

void ComputerPlayer::PlayGame(bool GameOver,int Card,GameBoard *Board, Deck SorryDeck) { // This function plays the game for a ComputerPlayer
    printLocation(this); // call again after case statement
    cout << endl;
    int PawnChosen;
    char PlayerChoice;
    int PieceChoice;
    int SpacestoMove;
    int counter = 0;
    int tempCard = 0;
    char Choice;

    string outputColor = this->color;
    for (char &c: outputColor) {
        c = c & ~' ';
    }
    cout << outputColor << " has drawn the " << Card << " card." << endl; // shows the drawn card

    switch (Card) {
        case 1:
            PawnChosen = randomPawn(); // random pawn selection

            if (((Board->SorryBoard[this->piece[0].StartLocation].occupied) &&
                (this->color == Board->SorryBoard[this->piece[0].StartLocation].playeronspace->color)) &&
                (this->piece[PawnChosen - 1].Start)) { // occupied by same color, and you want to move out of start. Turn is lost.
                cout << "Turn is lost." << endl;
                return;
            }

            while ((this->piece[PawnChosen - 1].Home)) { // finds a pawn until it is valid piece to move
                PawnChosen = randomPawn();
            }
            if (this->piece[PawnChosen - 1].Start && !this->piece[PawnChosen - 1].Home &&
                !this->piece[PawnChosen - 1].SafetyZone) { // move a piece out of Start
                cout << outputColor << " has chosen piece " << PawnChosen
                     << ". It has been moved out of the starting location." << endl;
                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, 0);
                //return;
            }
            if (!this->piece[PawnChosen - 1].Start && !this->piece[PawnChosen - 1].Home) { // move a piece forward one
                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card);
            }

            break;
        case 2:
            PawnChosen = randomPawn(); // random pawn is chosen
            if (((Board->SorryBoard[this->piece[0].StartLocation].occupied) &&
                 (this->color == Board->SorryBoard[this->piece[0].StartLocation].playeronspace->color)) &&
                (this->piece[PawnChosen - 1].Start)) { // occupied by same color, and you want to move out of start. Turn is lost.
                cout << "Turn is lost." << endl;
                return;
            }
            while ((this->piece[PawnChosen - 1].Home)) { // finds a pawn until it is valid piece to move
                PawnChosen = randomPawn();
            }
            if (this->piece[PawnChosen - 1].Start && !this->piece[PawnChosen - 1].Home &&
                !this->piece[PawnChosen - 1].SafetyZone) { // moves pawn out of Start
                cout << outputColor << " has chosen piece " << PawnChosen
                     << ". It has been moved out of the starting location." << endl;
                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, 0); // sets location
            }
            else if (!this->piece[PawnChosen - 1].Start && !this->piece[PawnChosen - 1].Home) { // moves pawn two spaces forward
                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // sets location
            }
            cout << outputColor << " has earned another turn!" << endl;
            cout << endl;
            this->PlayGame(GameOver, SorryDeck.DealCard(), Board, SorryDeck); // calls PlayGame to mimic another turn given
            break;

        case 3:
            counter = 0;
            PawnChosen = randomPawn(); // random pawn selected
            if (this->piece[0].Start && this->piece[1].Start && this->piece[2].Start &&
                this->piece[3].Start) { // cannot move since all pieces are in start
                cout << "A 3 cannot move a piece out of start. " << outputColor << " has lost their turn." << endl;
                return;
            } else {
                for (int i = 0; i < 4; i++) {
                    if (!this->piece[i].Home && !this->piece[i].Start) { // checks to see if all pieces are in Start or Home,
                        counter++;
                    }
                }
            }
            if (counter > 0) {
                while ((this->piece[PawnChosen - 1].Start && !this->piece[PawnChosen - 1].Home) ||
                       (!this->piece[PawnChosen - 1].Start && this->piece[PawnChosen - 1].Home)) { // find a pawn until it is valid piece to move
                    PawnChosen = randomPawn();
                }


                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // moves piece 3 spaces forward

            } else {
                cout << "No pieces can be moved. You lose your turn." << endl;
            }
            break;
        case 4:
            counter = 0;
            PawnChosen = randomPawn(); // random pawn selected
            if (this->piece[0].Start && this->piece[1].Start && this->piece[2].Start &&
                this->piece[3].Start) { // cannot move since all pieces are in start
                cout << "A 4 cannot move a piece out of start. " << outputColor << " has lost their turn." << endl;
                return;
            } else {
                for (int i = 0; i < 4; i++) {
                    if (!this->piece[i].Home && !this->piece[i].Start) { // checks to see if all pieces are in Start or Home,
                        counter++;
                    }
                }
            }
            if (counter > 0) {
                while ((this->piece[PawnChosen - 1].Start && !this->piece[PawnChosen - 1].Home) ||
                       (!this->piece[PawnChosen - 1].Start && this->piece[PawnChosen - 1].Home)) { // find a pawn until it is valid piece to move
                    PawnChosen = randomPawn();
                }
                if (this->piece[PawnChosen - 1].SafetyZone) { // checks to see if piece is in safety zone
                    cout << "You cannot move a piece out of Safety Zone. You lose your turn." << endl;
                }
                else {
                    this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, -Card); // moves back 4 spaces
                }
            } else {
                cout << "No pieces can be moved. You lose your turn." << endl;
            }
            break;
        case 5:
            counter = 0;
            PawnChosen = randomPawn(); // random pawn selected
            if (this->piece[0].Start && this->piece[1].Start && this->piece[2].Start &&
                this->piece[3].Start) { // checks to see if all pieces are in start
                cout << "A 5 cannot move a piece out of start. " << outputColor << " has lost their turn." << endl;
                return;
            } else {
                for (int i = 0; i < 4; i++) {
                    if (!this->piece[i].Home && !this->piece[i].Start) { // checks to see if all pieces are in Start or Home,
                        counter++;
                    }
                }
            }
            if (counter > 0) {
                while ((this->piece[PawnChosen - 1].Start && !this->piece[PawnChosen - 1].Home) ||
                       (!this->piece[PawnChosen - 1].Start && this->piece[PawnChosen - 1].Home)) { // find a pawn until it is valid piece to move
                    PawnChosen = randomPawn();
                }


                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // moves piece 5 spaces forward
            } else {
                cout << "No pieces can be moved. You lose your turn." << endl;
            }
            break;
        case 7:
            counter = 0;
            PawnChosen = randomPawn(); // random pawn selected
            if (this->piece[0].Start && this->piece[1].Start && this->piece[2].Start &&
                this->piece[3].Start) { // checks to see if all pieces are in Start
                cout << "A 7 cannot move a piece out of start. " << outputColor << " has lost their turn." << endl;
                return;
            } else {
                for (int i = 0; i < 4; i++) {
                    if (!this->piece[i].Home && !this->piece[i].Start) { // checks to see if all pieces are in Start or Home,
                        counter++;
                    }
                }
            }
            if (counter > 0) {
                while ((this->piece[PawnChosen - 1].Start && !this->piece[PawnChosen - 1].Home) ||
                       (!this->piece[PawnChosen - 1].Start && this->piece[PawnChosen - 1].Home)) { // find a pawn until it is valid piece to move
                    PawnChosen = randomPawn();
                }


                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // move piece 7 spaces forward

            } else {
                cout << "No pieces can be moved. You lose your turn." << endl;
            }
            break;
        case 8:
            counter = 0;
            PawnChosen = randomPawn(); // random pawn selected
            if (this->piece[0].Start && this->piece[1].Start && this->piece[2].Start &&
                this->piece[3].Start) {  // checks to see if all pieces are in Start
                cout << "A 8 cannot move a piece out of start. " << outputColor << " has lost their turn." << endl;
                return;
            } else {
                for (int i = 0; i < 4; i++) {
                    if (!this->piece[i].Home && !this->piece[i].Start) { // checks to see if all pieces are in Start or Home,
                        counter++;
                    }
                }
            }
            if (counter > 0) {
                while ((this->piece[PawnChosen - 1].Start && !this->piece[PawnChosen - 1].Home) ||
                       (!this->piece[PawnChosen - 1].Start && this->piece[PawnChosen - 1].Home)) { // find a pawn until it is valid piece to move
                    PawnChosen = randomPawn();
                }


                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // move pawn 8 spaces forward
            } else {
                cout << "No pieces can be moved. You lose your turn." << endl;
            }
            break;
        case 10:
            counter = 0;
            PawnChosen = randomPawn(); // random pawn selected
            if (this->piece[0].Start && this->piece[1].Start && this->piece[2].Start &&
                this->piece[3].Start) { // // checks to see if all pieces are in Start
                cout << "A 10 cannot move a piece out of start. " << outputColor << " has lost their turn." << endl;
                return;
            } else {
                for (int i = 0; i < 4; i++) {
                    if (!this->piece[i].Home && !this->piece[i].Start) { // checks to see if all pieces are in Start or Home,
                        counter++;
                    }
                }
            }
            if (counter > 0) {
                while ((this->piece[PawnChosen - 1].Start && !this->piece[PawnChosen - 1].Home) ||
                       (!this->piece[PawnChosen - 1].Start && this->piece[PawnChosen - 1].Home)) { // find a pawn until it is valid piece to move
                    PawnChosen = randomPawn();
                }


                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // moves piece 10 spaces forward
            } else {
                cout << "No pieces can be moved. You lose your turn." << endl;
            }
            break;
        case 12:
            counter = 0;
            PawnChosen = randomPawn(); // random pawn selected
            if (this->piece[0].Start && this->piece[1].Start && this->piece[2].Start &&
                this->piece[3].Start) { // checks to see if all pieces are in Start
                cout << "A 12 cannot move a piece out of start. " << outputColor << " has lost their turn." << endl;
                return;
            } else {
                for (int i = 0; i < 4; i++) {
                    if (!this->piece[i].Home && !this->piece[i].Start) { // checks to see if all pieces are in Start or Home,
                        counter++;
                    }
                }
            }
            if (counter > 0) {
                while ((this->piece[PawnChosen - 1].Start && !this->piece[PawnChosen - 1].Home) ||
                       (!this->piece[PawnChosen - 1].Start && this->piece[PawnChosen - 1].Home)) { // find a pawn until it is valid piece to move
                    PawnChosen = randomPawn();
                }


                this->piece[PawnChosen - 1].location = CheckBoard(this, Board, PawnChosen - 1, Card); // moves forward 12 spaces
            } else {
                cout << "No pieces can be moved. You lose your turn." << endl;
            }
            break;
        default:
            break;
    }
    cout << endl;
    if (Card != 2) { // if card is 2, it wont print again since it is being called recursively.
        printLocation(this);
    }
}

void GameBoard::createboard(){ //creates the board in the orientation RBYG

    for(int i = 0; i < 84;i++){

        SorryBoard[i].occupied = false;

        switch(i) {
            case(1):
                SorryBoard[i].color = "red";//red
                SorryBoard[i].type = 's'; //slide + 4
                break;
            case(2):
                SorryBoard[i].color = "red";//red
                SorryBoard[i].type = 'h'; //home
                break;
            case(9):
                SorryBoard[i].color = "red";//red
                SorryBoard[i].type = 'l'; //long slide + 5
                break;
            case(16):
                SorryBoard[i].color = "blue";//blue
                SorryBoard[i].type = 's'; //slide + 4
                break;
            case(17):
                SorryBoard[i].color = "blue";//blue
                SorryBoard[i].type = 'h'; //home
                break;
            case(24):
                SorryBoard[i].color = "blue";//blue
                SorryBoard[i].type = 'l'; //long slide + 5
                break;
            case(31):
                SorryBoard[i].color = "yellow";//yellow
                SorryBoard[i].type = 's'; //slide + 4
                break;
            case(32):
                SorryBoard[i].color = "yellow";//yellow
                SorryBoard[i].type = 'h'; //home
                break;
            case(39):
                SorryBoard[i].color = "yellow";//yellow
                SorryBoard[i].type = 'l'; //long slide + 5
                break;
            case(46):
                SorryBoard[i].color = "green";//green
                SorryBoard[i].type = 's'; //slide + 4
                break;
            case(47):
                SorryBoard[i].color = "green";//green
                SorryBoard[i].type = 'h'; //home
                break;
            case(54):
                SorryBoard[i].color = "green";//green
                SorryBoard[i].type = 'l'; //long slide + 5
                break;
            case(65):
                SorryBoard[i].color = "red";//red
                SorryBoard[i].type = 'e'; //end
                break;
            case(71):
                SorryBoard[i].color = "blue";//blue
                SorryBoard[i].type = 'e'; //end
                break;
            case(77):
                SorryBoard[i].color = "yellow";//yellow
                SorryBoard[i].type = 'e'; //end
                break;
            case(83):
                SorryBoard[i].color = "green";//blue
                SorryBoard[i].type = 'e'; //end
                break;
            default:
                SorryBoard[i].color = "none";//no color
                SorryBoard[i].type = 'n'; //no type
                break;

        }

    }
    cout << "The Sorry! Board has been created" << endl;
}

void Play11or13Human(Player* active,int Card, GameBoard *Board, Player* inactivePlayer1,Player* inactivePlayer2, Player*inactivePlayer3) { // This function does the cases of card 11 and the Sorry Card.
    printLocation(active); // call again after case statement
    cout << endl;
    string outputColor = active->color;
    for (char &c: outputColor) { // prints out the color in Uppercase
        c = c & ~' ';
    }
    if (Card == 13){ // Card 13 is the Sorry card
        cout << outputColor << " has drawn the SORRY card." << endl;
    }
    else {
        cout << outputColor << " has drawn the " << Card << " card." << endl; // outputs the card drawn
    }
    int PawnChosen;
    char PlayerChoice;
    int counter = 0;
    int counter1 = 0;
    int PieceChoice;
    int tempLocation;
    int SpacestoMove;
    int tempCard;
    char Choice;
    Player *inactivePlayerArray[3];
    inactivePlayerArray[0] = inactivePlayer1; // the other players are sent in to check swap feature
    inactivePlayerArray[1] = inactivePlayer2;
    inactivePlayerArray[2] = inactivePlayer3;
    switch (Card) {
        case 11:
            counter1 = 0;
            for (int i = 0; i < 4; i++){
                if (active->piece[i].Start || active->piece[i].Home){ // checks to see if all pieces are in Start or Home,
                    counter1++;
                }
            }
            if (counter1 == 4) {
                cout << "There are no pieces that you can move." << endl;
                return;
            }
            if (!active->piece[0].Start || !active->piece[1].Start || !active->piece[2].Start ||
                !active->piece[3].Start) { // choice between moving forward 11 or swapping with another player
                counter = 0;
                cout << "Type Y (to move 11 spaces forward). Type N (to swap positions with another player's pawn)"
                     << endl;
                cin >> Choice;
                if ((Choice == 'Y' || Choice == 'y')) { // move forward 11 case
                    cout << "Pick a piece to move" << endl;
                    cout << "1, 2, 3, or 4" << endl;
                    while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                           active->piece[PawnChosen - 1].Start) { // failsafe
                        cin.clear(); //clear bad input flag
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                        cout << "Invalid input; please re-enter.\n";
                    }
                    active->piece[PawnChosen - 1].location = CheckBoard(active, Board, PawnChosen - 1, Card); // moves the piece 11 spaces forward
                }
                for (int i = 0; i < 3; i++) { // trys to find if there is a piece valid to swap with
                    if (active->color != inactivePlayerArray[i]->color) {
                        for (int j = 0; j < 4; j++) {
                            if (!inactivePlayerArray[i]->piece[j].Start && !inactivePlayerArray[i]->piece[j].Home &&
                                !inactivePlayerArray[i]->piece[j].SafetyZone) {
                                counter++;
                            }
                        }
                    }
                }
                if ((Choice == 'N' || Choice == 'n') && (counter > 0)) { // swapping pieces case
                    counter = 0;
                    cout << "Pick a piece to swap with" << endl;
                    cout << "1, 2, 3, or 4" << endl;
                    while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                           (active->piece[PawnChosen - 1].Start)) { // failsafe
                        cin.clear(); //clear bad input flag
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                        cout << "Invalid input; please re-enter.\n";
                    }
                    cout << "You have chosen piece " << PawnChosen << endl;
                    cout << "Below is a list of pieces that are available to swap places with" << endl;
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 4; j++) { // prompts the valid pieces that can be swapped with
                            if (!inactivePlayerArray[i]->piece[j].Start && !inactivePlayerArray[i]->piece[j].Home &&
                                !inactivePlayerArray[i]->piece[j].SafetyZone) {
                                //counter++;
                                cout << "Player " << inactivePlayerArray[i]->color << ": Piece " << j + 1 << endl;
                            }
                        }
                    }

                    cout
                            << "What player would you like to swap with? (Type 'r', 'b', 'y', 'g'). You cannot choose your own color."
                            << endl;
                    cin >> PlayerChoice;
                    cout << "What piece of the player you chose would you like to swap with? (Type '1', '2', '3', '4')"
                         << endl;
                    cin >> PieceChoice;
                    if (PlayerChoice == 'r' || PlayerChoice == 'R') { // Red player case
                        for (int i = 0; i < 3; i++) {
                            if (inactivePlayerArray[i]->color == "red") {
                                if (!inactivePlayerArray[i]->piece[PieceChoice - 1].Start &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].Home &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].SafetyZone) { // swaps the location and pointer of the pieces
                                    tempLocation = active->piece[PawnChosen - 1].location;
                                    active->piece[PawnChosen - 1].location = inactivePlayerArray[i]->piece[PieceChoice -1].location;
                                    Board->SorryBoard[active->piece[PawnChosen-1].location].playeronspace = &active->piece[PawnChosen-1];
                                    inactivePlayerArray[i]->piece[PieceChoice - 1].location = tempLocation;
                                    Board->SorryBoard[tempLocation].playeronspace = inactivePlayerArray[i]->piece;
                                } else { // calls function again if player types an invalid piece
                                    cout << "Invalid input; please do your turn again.\n";
                                    Play11or13Human(active,Card, Board, inactivePlayer1, inactivePlayer2, inactivePlayer3);
                                }
                            }
                        }
                    } else if (PlayerChoice == 'b' || PlayerChoice == 'B') { // blue player case
                        for (int i = 0; i < 3; i++) {
                            if (inactivePlayerArray[i]->color == "blue") {
                                if (!inactivePlayerArray[i]->piece[PieceChoice - 1].Start &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].Home &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].SafetyZone) { // swaps the location and pointer of the pieces
                                    tempLocation = active->piece[PawnChosen - 1].location;
                                    active->piece[PawnChosen - 1].location = inactivePlayerArray[i]->piece[PieceChoice -1].location;
                                    Board->SorryBoard[active->piece[PawnChosen-1].location].playeronspace = &active->piece[PawnChosen-1];
                                    inactivePlayerArray[i]->piece[PieceChoice - 1].location = tempLocation;
                                    Board->SorryBoard[tempLocation].playeronspace = inactivePlayerArray[i]->piece;
                                } else { // calls function again if player types an invalid piece
                                    cout << "Invalid input; please do your turn again.\n";
                                    Play11or13Human(active, Card, Board, inactivePlayer1, inactivePlayer2, inactivePlayer3);
                                }
                            }
                        }
                    } else if (PlayerChoice == 'y' || PlayerChoice == 'Y') { // yellow player case
                        for (int i = 0; i < 3; i++) {
                            if (inactivePlayerArray[i]->color == "yellow") {
                                if (!inactivePlayerArray[i]->piece[PieceChoice - 1].Start &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].Home &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].SafetyZone) { // swaps the location and pointer of the pieces
                                    tempLocation = active->piece[PawnChosen - 1].location;
                                    active->piece[PawnChosen - 1].location = inactivePlayerArray[i]->piece[PieceChoice -1].location;
                                    Board->SorryBoard[active->piece[PawnChosen-1].location].playeronspace = &active->piece[PawnChosen-1];
                                    inactivePlayerArray[i]->piece[PieceChoice - 1].location = tempLocation;
                                    Board->SorryBoard[tempLocation].playeronspace = inactivePlayerArray[i]->piece;
                                } else { // calls function again if player types an invalid piece
                                    cout << "Invalid input; please do your turn again.\n";
                                    Play11or13Human(active, Card, Board, inactivePlayer1, inactivePlayer2, inactivePlayer3);
                                }
                            }
                        }
                    } else if (PlayerChoice == 'g' || PlayerChoice == 'G') { // green player case
                        for (int i = 0; i < 3; i++) {
                            if (inactivePlayerArray[i]->color == "green") {
                                if (!inactivePlayerArray[i]->piece[PieceChoice - 1].Start &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].Home &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].SafetyZone) { // swaps the location and pointer of the pieces
                                    tempLocation = active->piece[PawnChosen - 1].location;
                                    active->piece[PawnChosen - 1].location = inactivePlayerArray[i]->piece[PieceChoice -1].location;
                                    Board->SorryBoard[active->piece[PawnChosen-1].location].playeronspace = &active->piece[PawnChosen-1];
                                    inactivePlayerArray[i]->piece[PieceChoice - 1].location = tempLocation;
                                    Board->SorryBoard[tempLocation].playeronspace = inactivePlayerArray[i]->piece;
                                } else { // calls function again if player types an invalid piece
                                    cout << "Invalid input; please do your turn again.\n";
                                    Play11or13Human(active, Card, Board, inactivePlayer1, inactivePlayer2, inactivePlayer3);
                                }
                            }
                        }
                    }
                }
            }
            else {
                cout << "All pieces are in Start. You lose your turn." << endl;
            }
                break;

                case 13:
                    counter = 0;
                for (int i = 0; i < 3; i++) {
                    if (active->color != inactivePlayerArray[i]->color) { // checks to see if there are valid pieces to swap with
                        for (int j = 0; j < 4; j++) {
                            if (!inactivePlayerArray[i]->piece[j].Start && !inactivePlayerArray[i]->piece[j].Home &&
                                !inactivePlayerArray[i]->piece[j].SafetyZone) {
                                counter++;
                            }
                        }
                    }
                }
                if ((active->piece[0].Start || active->piece[1].Start || active->piece[2].Start ||
                     active->piece[3].Start) && (counter > 0)) { // swapping a piece out of Start with a piece on the board
                    counter = 0;
                    cout << "Pick a piece to move out of your starting location" << endl;
                    cout << "1, 2, 3, or 4" << endl;
                    while (!(cin >> PawnChosen) || (PawnChosen < 1 || PawnChosen > 4) ||
                           (!active->piece[PawnChosen - 1].Start)) {
                        cin.clear(); //clear bad input flag
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                        cout << "Invalid input; please re-enter.\n";
                    }
                    cout << "You have chosen piece " << PawnChosen << endl;
                    cout << "Below is a list of pieces that are available to swap places with" << endl;
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (!inactivePlayerArray[i]->piece[j].Start && !inactivePlayerArray[i]->piece[j].Home &&
                                !inactivePlayerArray[i]->piece[j].SafetyZone) {
                                //counter++;
                                cout << "Player " << inactivePlayerArray[i]->color << ": Piece " << j + 1 << endl;
                            }
                        }
                    }

                    cout
                            << "What player would you like to swap with? (Type 'r', 'b', 'y', 'g'). You cannot choose your own color."
                            << endl;
                    cin >> PlayerChoice;
                    cout << "What piece of the player you chose would you like to swap with? (Type '1', '2', '3', '4')"
                         << endl;
                    cin >> PieceChoice;
                    if (PlayerChoice == 'r' || PlayerChoice == 'R') { // red player case
                        for (int i = 0; i < 3; i++) {
                            if (inactivePlayerArray[i]->color == "red") {
                                if (!inactivePlayerArray[i]->piece[PieceChoice - 1].Start &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].Home &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].SafetyZone) {
                                    active->piece[PawnChosen - 1].Start = false; // swaps the location and pointer of your piece to the chosen piece's location and sends the other piece back to Start
                                    active->piece[PawnChosen - 1].location = inactivePlayerArray[i]->piece[PieceChoice -1].location;
                                    Board->SorryBoard[active->piece[PawnChosen-1].location].playeronspace = &active->piece[PawnChosen-1];
                                    inactivePlayerArray[i]->piece[PieceChoice -1].location = inactivePlayerArray[i]->piece[PieceChoice - 1].StartLocation;
                                    inactivePlayerArray[i]->piece[PieceChoice - 1].Start = true;
                                } else { // calls function again if player types an invalid piece
                                    cout << "Invalid input; please do your turn again.\n";
                                    Play11or13Human(active,Card, Board, inactivePlayer1, inactivePlayer2, inactivePlayer3);
                                }
                            }
                        }
                    } else if (PlayerChoice == 'b' || PlayerChoice == 'B') { // blue player case
                        for (int i = 0; i < 3; i++) {
                            if (inactivePlayerArray[i]->color == "blue") {
                                if (!inactivePlayerArray[i]->piece[PieceChoice - 1].Start &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].Home &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].SafetyZone) {
                                    active->piece[PawnChosen - 1].Start = false; // swaps the location and pointer of your piece to the chosen piece's location and sends the other piece back to Start
                                    active->piece[PawnChosen - 1].location = inactivePlayerArray[i]->piece[PieceChoice -1].location;
                                    Board->SorryBoard[active->piece[PawnChosen-1].location].playeronspace = &active->piece[PawnChosen-1];
                                    inactivePlayerArray[i]->piece[PieceChoice -1].location = inactivePlayerArray[i]->piece[PieceChoice - 1].StartLocation;
                                    inactivePlayerArray[i]->piece[PieceChoice - 1].Start = true;
                                } else { // calls function again if player types an invalid piece
                                    cout << "Invalid input; please do your turn again.\n";
                                    Play11or13Human(active,Card, Board, inactivePlayer1, inactivePlayer2, inactivePlayer3);
                                }
                            }
                        }
                    } else if (PlayerChoice == 'y' || PlayerChoice == 'Y') { // yellow player case
                        for (int i = 0; i < 3; i++) {
                            if (inactivePlayerArray[i]->color == "yellow") {
                                if (!inactivePlayerArray[i]->piece[PieceChoice - 1].Start &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].Home &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].SafetyZone) {
                                    active->piece[PawnChosen - 1].Start = false; // swaps the location and pointer of your piece to the chosen piece's location and sends the other piece back to Start
                                    active->piece[PawnChosen - 1].location = inactivePlayerArray[i]->piece[PieceChoice -1].location;
                                    Board->SorryBoard[active->piece[PawnChosen-1].location].playeronspace = &active->piece[PawnChosen-1];
                                    inactivePlayerArray[i]->piece[PieceChoice -1].location = inactivePlayerArray[i]->piece[PieceChoice - 1].StartLocation;
                                    inactivePlayerArray[i]->piece[PieceChoice - 1].Start = true;
                                }
                                else { // calls function again if player types an invalid piece
                                    cout << "Invalid input; please do your turn again.\n";
                                    Play11or13Human(active,Card, Board, inactivePlayer1, inactivePlayer2, inactivePlayer3);
                                }
                            }
                        }
                    } else if (PlayerChoice == 'g' || PlayerChoice == 'G') { // green player case
                        for (int i = 0; i < 3; i++) {
                            if (inactivePlayerArray[i]->color == "green") {
                                if (!inactivePlayerArray[i]->piece[PieceChoice - 1].Start &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].Home &&
                                    !inactivePlayerArray[i]->piece[PieceChoice - 1].SafetyZone) {
                                    active->piece[PawnChosen - 1].Start = false; // swaps the location and pointer of your piece to the chosen piece's location and sends the other piece back to Start
                                    active->piece[PawnChosen - 1].location = inactivePlayerArray[i]->piece[PieceChoice - 1].location;
                                    Board->SorryBoard[active->piece[PawnChosen-1].location].playeronspace = &active->piece[PawnChosen-1];
                                    inactivePlayerArray[i]->piece[PieceChoice -1].location = inactivePlayerArray[i]->piece[PieceChoice - 1].StartLocation;
                                    inactivePlayerArray[i]->piece[PieceChoice - 1].Start = true;
                                } else { // calls function again if player types an invalid piece
                                    cout << "Invalid input; please do your turn again.\n";
                                    Play11or13Human(active,Card, Board, inactivePlayer1, inactivePlayer2, inactivePlayer3);
                                }
                            }
                        }
                    }
                }
                else {
                        cout << "There are no players to swap with. You lose your turn." << endl;
                        return;
                }
                    break;
                    default:
                        break;
                }
                printLocation(active); // prints current location of all pieces
            }

void Play11or13Computer(Player* active,int Card, GameBoard *Board, Player *inactivePlayer1, Player *inactivePlayer2,
                                Player *inactivePlayer3) { // this function plays the cards of 11 and 13 for a Computer Player.
    cout << endl;
    if (Card == 13){ // The card 13 draws a SORRY card.
        cout << "You have drawn the SORRY card." << endl;
    }
    else {
        cout << "You have drawn the " << Card << " card." << endl; // shows the card drawn
    }
    int PawnChosen;
    char PlayerChoice;
    int counter = 0;
    int counter1 = 0;
    int PieceChoice;
    int tempLocation;
    int SpacestoMove;
    int tempCard;
    char Choice;
    string outputColor = active->color;
    for (char &c: outputColor) { // outputs color onto screen in uppercase letters
        c = c & ~' ';
    }
    Player *inactivePlayerArray[3];
    inactivePlayerArray[0] = inactivePlayer1;
    inactivePlayerArray[1] = inactivePlayer2;
    inactivePlayerArray[2] = inactivePlayer3;
    switch (Card) {
        case 11:
            counter = 0;
            PawnChosen = randomPawn(); // random pawn chosen
        if(active->piece[0].Start && active->piece[1].Start && active->piece[2].Start &&
           active->piece[3].Start){ // checks to see if all players are in Start.
            cout << "A 11 cannot move a piece out of start. " << outputColor << " has lost their turn." << endl;
            return;
        }
        else {
            for (int i = 0; i < 4; i++) {
                if (!active->piece[i].Home && !active->piece[i].Start) { // checks to see if all players are in Start or Home.
                    counter++;
                }
            }
        }

        if(counter > 0) {
            while (active->piece[PawnChosen - 1].Start || active->piece[PawnChosen - 1].Home){
                PawnChosen = randomPawn(); // find a pawn until it is valid piece to move
            }
            active->piece[PawnChosen - 1].location = CheckBoard(active, Board, PawnChosen - 1, Card); // moves piece 11 spaces forward
        }
        else{
            cout << "No pieces can be moved. You lose your turn." << endl;
        }
        break;
        case 13:
            counter = 0;
            counter1 = 0;
            PawnChosen = randomPawn(); // random pawn is chosen
            for (int i = 0; i < 3; i++) {
                if (active->color != inactivePlayerArray[i]->color) {
                    for (int j = 0; j < 4; j++) { // find all valid pieces to swap with
                        if (!inactivePlayerArray[i]->piece[j].Start && !inactivePlayerArray[i]->piece[j].Home &&
                            !inactivePlayerArray[i]->piece[j].SafetyZone) {
                            counter++;

                        }
                    }
                }
            }
            if (!active->piece[0].Start && !active->piece[1].Start && !active->piece[2].Start &&
                !active->piece[3].Start) { // checks to see if all pieces are not in Start
                cout << "A Sorry card cannot move a piece that is already out of start. " << outputColor
                     << " has lost their turn." << endl;
                return;
            }
            else if (counter == 0) { // checks to see if other players have pieces out of start
                cout << "No other players have pieces that are out of Start. " << outputColor << " has lost their turn."
                     << endl;
                return;
            }
            else {
                for (int i = 0; i < 4; i++) { // checks to see if the active player has a piece in start
                    if (!active->piece[i].Home && !active->piece[i].SafetyZone && active->piece[i].Start) {
                        counter1++;
                    }
                }
                if (counter1 > 0) {
                    while (!active->piece[PawnChosen - 1].Start || active->piece[PawnChosen - 1].Home ||
                           active->piece[PawnChosen - 1].SafetyZone) {
                        PawnChosen = randomPawn(); // find a pawn until it is valid piece to move
                    }
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (!inactivePlayerArray[i]->piece[j].Start &&
                                !inactivePlayerArray[i]->piece[j].Home &&
                                !inactivePlayerArray[i]->piece[j].SafetyZone) { // finds a player that is valid to swap with
                                active->piece[PawnChosen - 1].Start = false; // sets the location and pointer to the active piece and sends the inactive player to home
                                active->piece[PawnChosen - 1].location = inactivePlayerArray[i]->piece[j].location;
                                Board->SorryBoard[active->piece[PawnChosen-1].location].playeronspace = &active->piece[PawnChosen-1];
                                inactivePlayerArray[i]->piece[j].location = inactivePlayerArray[i]->piece[j].StartLocation;
                                inactivePlayerArray[i]->piece[j].Start = true;
                                cout << outputColor << "'s Piece " << PawnChosen
                                     << " has been chosen to move out of start and has been "
                                        "swapped with " << inactivePlayerArray[i]->color << "'s Piece "
                                     << j + 1 << ". " << endl << inactivePlayerArray[i]->color << "'s Piece " << j + 1
                                     << " has been sent home." << endl;
                                i = 3;
                                j = 4;
                                //active->piece[PawnChosen - 1].location = CheckBoard(active, Board, PawnChosen - 1, 0);
                            }
                        }
                    }
                }
                else {
                    cout << "No pieces can be moved. You lose your turn." << endl;
                    return;
                }
            }
            break;
        default: break;
    }
    printLocation(active); // prints location of pieces
}