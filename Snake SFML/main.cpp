#include "Game.h"

int main(int argc, char* argv[])
{

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    sf::Clock Clock;
    Game *game = new Game(argc, argv);
    game->init("Wonsz", 0, 0, 400, 450, false);
    while (game->running())
    {
        float elapseTime = Clock.getElapsedTime().asMilliseconds();
        Clock.restart();
        game->handleEvents();
        game->update(elapseTime);
        game->render();
    }
    game->clean();
    delete game;
    return 0;
}
int WinMain(int argc, char* argv[]) {
    main(argc,argv);
}