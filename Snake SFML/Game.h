#pragma once
#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#define PATH "save.txt"
class Game
{
public:
	Game();
	Game(int argc, char* argv[]);
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
	void handleEvents();
	void update(float elapseTime);
	void render();
	void clean();
	static sf::Event event;
	bool running() { return isRunning; }
	//static sf::RenderTexture textureRenderer;
	static sf::RenderWindow* window;
	static void saveData(std::string path,int data);
	static void readData(std::string path,int *data);
	static sf::Font* font;
	static bool pause;
private:
	bool isRunning;
};

