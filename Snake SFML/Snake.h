#pragma once
#include "Game.h"
#include <algorithm>
class Snake
{
public:
	Snake(sf::Vector2i blockSize,sf::Vector2i offset,bool god = false);
	~Snake();
	void Draw();
	void update();
	void init();
	void events();
	void dead();
private:
	void removeSegment();
	bool isDead;
	float speed = 1;
	int score = 0;
	int Highscore = 0;
	sf::Vector2i blockSize;
	sf::Vector2i gridSize;
	sf::Vector2i offset;
	void generateApple();
	bool outsideofMap();
	int head;
	int tail;
	sf::Vector2i direction;
	std::vector<sf::Vector2i> body;
	sf::Vector2i apple;
	//Debug Tools
	bool god;
	bool noClip;
	bool bnoClip;
};

