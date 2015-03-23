#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include "coordinate.h"




class Game
{
private:
	    std::vector<Coordinate*> snake_;
	    int direction_;
	    Coordinate bonus_;
	    int state_;



public:
    sf::RenderWindow app;


	Game(int w, int h);
	~Game();

	void drawMap();
	void run();
	void win();
	void gameOver();
	void ia();

	std::vector<int> possibilities();
	int move(int a);
	int loopDetection();
	std::vector<int> calc();


	int getDirection(){return direction_;}
	void setDirection(int d){direction_ = d;}
	int getState(){return state_;}



};

int nb_true(std::vector<int> v);
int max(int a, int b, int c, int d);




#endif 