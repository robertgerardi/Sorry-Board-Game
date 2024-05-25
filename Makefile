all:
	g++ main.cpp GameObjects.cpp setupGame.cpp Shuffle.cpp -o game

run:
	./game < input.txt