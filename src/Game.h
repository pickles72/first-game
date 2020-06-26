#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videoMode;

    void initWindow();
    void initVariables();

public:
    Game(/* args */);
    virtual ~Game();

    const bool running() const;

    void pollEvents();
    void update();
    void render();
};

#endif