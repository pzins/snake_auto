sfml-app : main.o game.o coordinate.o
	g++ main.o game.o coordinate.o -o sfml-app -std=c++11 -L /home/pierre/SFML/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o : main.cpp game.cpp game.h coordinate.cpp coordinate.h
	g++ -c main.cpp game.cpp coordinate.cpp -std=c++11 -I /home/pierre/SFML/include

clean :
	rm sfml-app *.o
