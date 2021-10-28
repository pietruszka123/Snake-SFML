#include "Game.h"
#include "Snake.h"
#include "OpenSans-Medium.h"
sf::Event Game::event;
//sf::RenderTexture Game::textureRenderer;
sf::RenderWindow* Game::window;
sf::Font* Game::font;
bool Game::pause = true;
Snake* s;
bool god = false;
Game::Game()
{
}

Game::Game(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i) {
		if (std::string(argv[i]) == "--GodMode") {
			god = true;
			break;
		}
	}
}

Game::~Game()
{
	delete s;
	delete window;
	delete font;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
	int flags = sf::Style::Close;
	if (fullScreen) {
		flags = sf::Style::Fullscreen;
	}
	this->window = new sf::RenderWindow(sf::VideoMode(width, height), title,flags);
	window->setFramerateLimit(60);
	isRunning = true;
	font = new sf::Font();
	font->loadFromMemory(&OpenSans_Medium_ttf, OpenSans_Medium_ttf_len);
	s = new Snake(sf::Vector2i(25, 25), sf::Vector2i(0, 50), god);
}

void Game::handleEvents()
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			isRunning = false;
			return;
		}
		if (event.type == sf::Event::LostFocus) {
			pause = true;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape) {
			isRunning = false;
			return;
		}
	}
}

void Game::update(float elapseTime)
{
	s->update();
}

void Game::render()
{
	window->clear();

	s->Draw();

	window->display();
}

void Game::clean()
{
	window->close();
}
void Game::saveData(std::string path,int data)
{
	std::ofstream writeFile(path,std::ios::binary);
	if (writeFile.is_open()) {
		writeFile << data;
	}
	writeFile.close();
}

void Game::readData(std::string path, int*data)
{
	std::ifstream readFile(path, std::ios::binary);
	if (readFile.is_open()) {
		while (!readFile.eof())
		{
			readFile >> *data;
		}
	}
	readFile.close();
}
