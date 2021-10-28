#include "Snake.h"
sf::RectangleShape re;
sf::Clock c;
sf::Clock KeyTimer;
sf::Text text;
sf::RectangleShape box;
Snake::Snake(sf::Vector2i blockSize, sf::Vector2i offset = sf::Vector2i(0,0),bool god)
{
	this->offset = offset;
	this->blockSize = blockSize;
	re.setSize((sf::Vector2f)(this->blockSize - sf::Vector2i(1,1)));
	sf::Vector2i s = (sf::Vector2i)Game::window->getSize() - offset;
	gridSize = sf::Vector2i(s.x / blockSize.x, s.y / blockSize.y);
	this->god = god;
	Game::readData(PATH, &this->Highscore);
	std::cout << Highscore;
	text.setFont(*Game::font);

	box.setOutlineColor(sf::Color::Color(255, 255, 255, 200));
	box.setOutlineThickness(1);
	box.setSize((sf::Vector2f)s - sf::Vector2f(2, 1));
	box.setPosition((sf::Vector2f)offset - sf::Vector2f(-1,0));
	box.setFillColor(sf::Color::Color(0, 0, 0, 0));
	init();

}
void Snake::generateApple()
{
	apple = sf::Vector2i(rand() % gridSize.x, rand() % gridSize.y);
	while (std::find(body.begin(),body.end(),apple) != body.end())
	{
		apple = sf::Vector2i(rand() % gridSize.x, (rand() % gridSize.y));
	}
}
void Snake::init()
{
	head = 0;
	tail = 0;
	direction = sf::Vector2i(1, 0);
	body.clear();
	
	body.push_back(sf::Vector2i(gridSize.x / 2, gridSize.y / 2));
	isDead = false;
	generateApple();

	score = 0;
}
void Snake::events()
{
	if (KeyTimer.getElapsedTime().asMilliseconds() > 500) {
		if (!isDead &&( sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {
			KeyTimer.restart();
				Game::pause = !Game::pause;
				return;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			KeyTimer.restart();
			init();
		}
	}
	if (Game::pause || isDead)return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			direction.y = 1;
			direction.x = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		direction.y = -1;
		direction.x = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		direction.y = 0;
		direction.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		direction.y = 0;
		direction.x = 1;
	}
}
Snake::~Snake()
{
	Game::saveData(PATH, Highscore);
}
void Snake::Draw()
{
	re.setFillColor(sf::Color::Color(255, 0, 0, 255));
	re.setPosition(sf::Vector2f(apple.x * blockSize.x + offset.x, apple.y * blockSize.y + offset.y));
	Game::window->draw(re);
	for (int i = 0; i < body.size(); i++)
	{
		if(i == head)
		{
			re.setFillColor(sf::Color::Color(0, 74, 0, 255));
		}
		else
		re.setFillColor(sf::Color::Color(1, 122, 1, 255));
		sf::Vector2f t(blockSize.x * body[i].x + offset.x, blockSize.y * body[i].y + offset.y);
		re.setPosition(t);
		Game::window->draw(re);
	}
	if (!isDead) {
		text.setCharacterSize(15);
		text.setPosition(sf::Vector2f(0, 0));
		text.setString("Wynik: " + std::to_string(score) + "\nnajlepszy wynik: " + std::to_string(Highscore));
		Game::window->draw(text);

	}
	else{
		text.setCharacterSize(15);
		sf::Vector2f s = (sf::Vector2f)Game::window->getSize();
		text.setPosition(sf::Vector2f((s.x - text.getLocalBounds().width) / 2, (s.y - text.getLocalBounds().height) / 2) - (sf::Vector2f)offset);
		text.setString(L"Wynik koñcowy: " + std::to_wstring(score) + L"\nnajlepszy wynik: " + std::to_wstring(Highscore));
		Game::window->draw(text);
	}
	if (Game::pause && !isDead) {
		text.setCharacterSize(50);
		sf::Vector2f s = (sf::Vector2f)Game::window->getSize();
		text.setString("Pause");
		text.setPosition(sf::Vector2f((s.x - text.getLocalBounds().width) / 2, (s.y - text.getLocalBounds().height) / 2) - (sf::Vector2f)offset);
		Game::window->draw(text);
	}
	Game::window->draw(box);

}
bool Snake::outsideofMap()
{
	if (body[head].x + direction.x < 0 || body[head].y + direction.y < 0 || body[head].x + direction.x >= gridSize.x || body[head].y + direction.y >= gridSize.y) {
		return true;
	}
	return false;
}
void Snake::dead()
{
	isDead = true;
}
void Snake::removeSegment() {
	body.erase(body.begin());
}
void Snake::update()
{

	events();
	if (Game::pause || isDead)return;
	if (c.getElapsedTime().asMilliseconds() > 75 * speed) {
		
		if (outsideofMap() || std::find(body.begin(), body.end(), body[head] + direction) != body.end()) {
			if (!god) {
				dead();
			}
			return;
		}
		if (body[head] + direction == apple) {
			body.insert(body.begin(),body[tail]);
			head = body.size() - 1;
			generateApple();
			score++;
			if (score > Highscore)Highscore = score;
		}
		c.restart();
		body.push_back(body[head] + direction);
		body.erase(body.begin() + tail);
		head = body.size() - 1;
		tail = 0;

	}

}
