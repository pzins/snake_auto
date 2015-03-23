#include "game.h"
#include <ctime>
#define WIDTH_CASE 16
#define HEIGHT_CASE 16

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3


#define SIZE 40

//right = 0, up = 1; left = 2; down = 3
//x = num de ligne ; y = num de colonne
//croissant vers le bas et droite

Game::Game(int w, int h) : app(sf::VideoMode(w, h), "Snake", sf::Style::Default), direction_(0), bonus_(10,10), state_(0)
{
	Coordinate* c1 = new Coordinate(19,18);
	Coordinate* c2 = new Coordinate(19,19);
	Coordinate* c3 = new Coordinate(19,20);
	Coordinate* c4 = new Coordinate(19,21);
	Coordinate* c5 = new Coordinate(19,22);

	snake_.push_back(c1);
	snake_.push_back(c2);
	snake_.push_back(c3);
	snake_.push_back(c4);
	snake_.push_back(c5);



}


Game::~Game()
{

}


/**
* chargement des textures et sprites
* text_vect : vecteur contenant 12 textures : 0 à 11
* double boucle sur la matrice screen_ pour afficher chaque case (en créant une sprite à partir d'une texture)
*/
void Game::drawMap()
{
	sf::Texture fill;
    fill.loadFromFile("fill.png");
    fill.setSmooth(true);
   	
	sf::Texture bonus;
    bonus.loadFromFile("bonus.png");
    bonus.setSmooth(true);


    for (int i = 0; i < snake_.size(); ++i)
    {
        sf::Sprite sprite;
        sprite.setTexture(fill);
        sprite.setPosition(sf::Vector2f(snake_[i]->getY() * WIDTH_CASE,snake_[i]->getX() * HEIGHT_CASE));
        app.draw(sprite); 
        
    }

    sf::Sprite sprite;
    sprite.setTexture(bonus);
    sprite.setPosition(sf::Vector2f(bonus_.getY() * WIDTH_CASE,bonus_.getX() * HEIGHT_CASE));
    app.draw(sprite); 
    
}

void Game::run()
{
	Coordinate* c;
	switch(direction_)
	{
		case 0 : c = new Coordinate(snake_.back()->getX(),snake_.back()->getY() + 1);
		break;
		case 1 : c = new Coordinate(snake_.back()->getX() - 1 ,snake_.back()->getY());
		break;
		case 2 : c = new Coordinate(snake_.back()->getX(),snake_.back()->getY() - 1);
		break;
		case 3 : c = new Coordinate(snake_.back()->getX() + 1,snake_.back()->getY());
		break;
	}
	if (snake_.size() >= SIZE * SIZE)
	{
		state_ = 2;
		return;
	}
	bool gameover = false;
	if (c->getX() >= SIZE || c->getY() >= SIZE
		|| c->getX() < 0 || c->getY() < 0) gameover = true;
	for(int i = 0; i < snake_.size(); ++i)
	{
		if (snake_[i]->getX() == c->getX() && snake_[i]->getY() == c->getY())
		{
			gameover = true;
			break;
		}
	}
	if (gameover)
	{
		state_ = 1;
		return;
	}
	snake_.push_back(c);

	for(int i = 0; i < snake_.size() - 2; ++i)
	{
		snake_[i] = snake_[i + 1];
	}
	bool test = false;

	if(snake_[snake_.size() - 2]->getX() == bonus_.getX() && snake_[snake_.size() - 2]->getY() == bonus_.getY())
	{

	    int x = rand() % 40;
	    int y = rand() % 40;

	    bonus_.setX(x);
	    bonus_.setY(y);
	    test = true;

	}
	
	if(!test)
		snake_.erase(snake_.begin() + snake_.size() - 2);
}

void Game::win()
{
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Congratulations You Win !!!");
	text.setCharacterSize(70);
	text.setPosition(sf::Vector2f(100,300));
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Red);
	app.draw(text);
}

void Game::gameOver()
{
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Game Over");
	text.setCharacterSize(70);
	text.setPosition(sf::Vector2f(100,300));
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Red);
	app.draw(text);
}




std::vector<int> Game::possibilities()
{
	bool right = (snake_.back()->getY() + 1 < SIZE);
	bool left = (snake_.back()->getY() - 1 >= 0);
	bool up = (snake_.back()->getX() - 1 >= 0);
	bool down = (snake_.back()->getX() + 1 < SIZE) ;


	Coordinate r(snake_.back()->getX(), snake_.back()->getY() + 1);
	Coordinate l(snake_.back()->getX(), snake_.back()->getY() - 1);
	Coordinate u(snake_.back()->getX() - 1, snake_.back()->getY());
	Coordinate d(snake_.back()->getX() + 1, snake_.back()->getY());

/*
	Coordinate* r = new Coordinate(snake_.back()->getX(), snake_.back()->getY() + 1);
	Coordinate* l = new Coordinate(snake_.back()->getX(), snake_.back()->getY() - 1);
	Coordinate* u = new Coordinate(snake_.back()->getX() - 1, snake_.back()->getY());
	Coordinate* d = new Coordinate(snake_.back()->getX() + 1, snake_.back()->getY());
*/

	for(int i = 0; i < snake_.size(); ++i)
	{
		if (right && *(snake_[i]) == r) right = false;
		if (left && *(snake_[i]) == l) left = false;
		if (up && *(snake_[i]) == u) up = false;
		if (down && *(snake_[i]) == d) down = false;
	}
	std::vector<int> ret;
	ret.push_back(right);
	ret.push_back(up);
	ret.push_back(left);
	ret.push_back(down);
	return ret;
}


void Game::ia()
{
	//v recoit les possibilité de mouv: prochaine case à right, up, left ou down
	std::vector<int > v = possibilities();

	//boolean pr savoir si mouv OK
	bool right = v[0];
	bool up = v[1];
	bool left = v[2];
	bool down = v[3];

	//nb de mouv possibles
	int nb_possib = nb_true(v);

	//affichage
	//std::cout << right << " " << up << " " << left << " " << down << std::endl;





	int nb = 0;
	bool stop = false;
	int choice;

	//si pas de mouvement possible on quitte tt de suite la fonction
	if (!up && !down && !left && !right) return;

	//simulation coup suivant
	//nombre de direction possible en supposant d'aller à X maintenant
	int up_ = 0;
	int down_ = 0;
	int left_ = 0;
	int right_ = 0;

	Coordinate* c;

	int disabled = loopDetection();

	//si on peut aller à droite tt de suite
	if(right && disabled != RIGHT) right_ = move(RIGHT);
	if(up && disabled != UP) up_ = move(UP);
	if(left && disabled != LEFT) left_ = move(LEFT);
	if(down && disabled != DOWN) down_ = move(DOWN);

	if(up && left && right || up && left && down || left && right && down || down && up && right)
	{
		std::vector<int> vv = calc();
		for(int i = 0; i < vv.size(); ++i)
		{
			if(vv[i] == RIGHT) right_ = 0;
			if(vv[i] == LEFT) left_ = 0;
			if(vv[i] == UP) up_ = 0;
			if(vv[i] == DOWN) down_ = 0;
		}
	}

	//si 3 directions possible => va vers le bonus
	if (up && left && right || up && left && down || left && right && down || down && up && right)
	{
		//dirige snake vers le bonus
		if(up && bonus_.getX() < snake_.back()->getX()) direction_ = 1;
		else if (left && bonus_.getX() < snake_.back()->getX()) direction_ = 2;
		else if (down && bonus_.getX() > snake_.back()->getX()) direction_ = 3;
		else if (right && bonus_.getY() > snake_.back()->getY()) direction_ = 0;
	}
	else
	{
		

		//choice reçoit le max :
		// 0 : si en allant à droite maintenant il reste le plus d'options possibles au coup suivant
		// 1 : haut, 2 : gauche, 3 : bas
		direction_ = max(right_, up_, left_, down_);		
	}




}

int Game::move(int a)
{
	Coordinate* c;
	switch(a)
	{
		case RIGHT : c = new Coordinate(snake_.back()->getX(), snake_.back()->getY() + 1);break;
		case UP : c = new Coordinate(snake_.back()->getX() - 1, snake_.back()->getY());break;
		case LEFT : c = new Coordinate(snake_.back()->getX(), snake_.back()->getY() - 1);break;
		case DOWN : c = new Coordinate(snake_.back()->getX() + 1, snake_.back()->getY());break;
	}
	snake_.push_back(c);
	std::vector<int> temp = possibilities();
	int nb = nb_true(temp);
	snake_.pop_back();
	return nb;
}



int Game::loopDetection()
{
	int no = 5;
	for(int i = 0; i < snake_.size() - 1; ++i)
	{
		if(direction_ == RIGHT && snake_.back()->getX() == snake_[i]->getX() &&
			(snake_.back()->getY() + 2 == snake_[i]->getY() ||
			snake_.back()->getY() + 3 == snake_[i]->getY() ||
			snake_.back()->getY() + 1 == snake_[i]->getY()))
			no = RIGHT;
		else if(direction_ == UP && snake_.back()->getY() == snake_[i]->getY() &&
			(snake_.back()->getX() - 2 == snake_[i]->getX() ||
			snake_.back()->getX() - 3 == snake_[i]->getX() ||
			snake_.back()->getX() - 1 == snake_[i]->getX()))
			no = UP;		
		else if(direction_ == LEFT && snake_.back()->getX() == snake_[i]->getX() &&
			(snake_.back()->getY() - 2 == snake_[i]->getY() ||
			snake_.back()->getY() - 3 == snake_[i]->getY() ||
			snake_.back()->getY() - 1 == snake_[i]->getY()))
			no = LEFT;		
		else if(direction_ == UP && snake_.back()->getY() == snake_[i]->getY() &&
			(snake_.back()->getX() + 2 == snake_[i]->getX() ||
			snake_.back()->getX() + 3 == snake_[i]->getX() ||
			snake_.back()->getX() + 1 == snake_[i]->getX()))
			no = DOWN;
	}
	
	return no;
}

std::vector<int> Game::calc()
{
	float ne = 0, no = 0, so = 0, se = 0;
	for(int i = 0; i < snake_.size(); ++i)
	{
		if(snake_.back()->getX() < snake_[i]->getX())
		{
			if(snake_.back()->getY() < snake_[i]->getY())
			{
				++ne;
			}
			else
				++no;
		}
		else
		{
			if(snake_.back()->getY() < snake_[i]->getY())
			{
				++se;
			}
			else
			{
				++so;
			}
		}
	}
	ne /= snake_.size();
	no /= snake_.size();
	se /= snake_.size();
	so /= snake_.size();
	std::vector<int> v;
	if(ne > 0.8)
	{
		v.push_back(RIGHT);
		v.push_back(UP);
	}
	else if(no > 0.8)
	{
		v.push_back(LEFT);
		v.push_back(UP);
	}
	else if(so > 0.8)
	{
		v.push_back(DOWN);
		v.push_back(LEFT);
	}
	else if(se > 0.8)
	{
		v.push_back(DOWN);
		v.push_back(RIGHT);
	}
	return v;
}


int nb_true(std::vector<int> v)
{
	int res = 0;
	for(int i = 0; i < v.size(); ++i)
	{
		if(v[i]) ++res;
	}
	return res;
}

int max(int a, int b, int c, int d)
{
	std::vector<int> v;
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	v.push_back(d);

	int ret = *std::max_element(v.begin(),v.end());
	int nb = 0;
	do
	{
		nb = rand() % 4;

	} while(v[nb] != ret);
	return nb;
}