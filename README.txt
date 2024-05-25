Description: This project mimics the Sorry! board game. The project has a board, 4 players, and a turn based watch window presented 
in the terminal. This allows the viewer to watch the game run live.

Running the game: This can be done by gathering the files and putting them into a compiler (we used clion), and running the code. 
It should prompt if you would like to play, if you select no, the game runs fully with computer players.

If you want to use the make file, you can use Ubuntu ( or possibly another command prompt that can use make), go to the directory, 
and type in 'make all -f MakeFile' to compile all of the code, then 'make run -f MakeFile' to begin the game.

IF MAKE FILE DOES NOT WORK WE HAVE AN OUTPUT CALLED output.txt

Contributions: 
Ethan La Rue: Responsible for implementing the deck class which housed and managed all of the cards and also the shuffle feature that used the deck class and returned a shuffled version of it. He was also responsible for the majority of the write-up to be submitted. 
Robert Gerardi: Implemented the classes, structure and implementation for the computer player movement, pawn and player initialization, created the board and boardspace classes. Edited the writeup to reflect new changes and update for consistency. Although most of the commits were by me, a majority of the time, we were working on them together using group code on Clion. I created the README.txt.
Niraj Patel: Implemented the Player and Pawn classes, structure, and movement for the human player. Also, created all of the HumanPlayer class, including the structure and inheritance of the Player class. Created the prompting for the human player and developed failsafes for user interaction. Edited the writeup to show the necessary requirements that were needed for the project. 


***Although robert had most of the pushes to git, we worked on the project together in person and over clion collaboration tool

Interesting Features: The player can watch the game live by interacting with the screen and use unique pieces like 11, 7 , and SORRY!. Swap cards allow the user to pick pieces to swap with and other cards 
allow to move two pawns at once. The user has the ability to pick their desired color.

Status Report: We think the games runs almost perfectly. Their may be a bug rarely but we have been able to eliminate basically all of the bugs.
