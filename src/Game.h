#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>

class Game
{
private:
    // Window
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videoMode;

    // Mouse Position
    sf::Vector2i mousePosWindow;

    // Game Logic
    int points;

    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;

    // Enemy
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    // Private Methods
    void initWindow();
    void initVariables();
    void initEnemies();

public:
    // Constructors / Destructors
    Game(/* args */);
    virtual ~Game();

    // Accessors
    const bool running() const;

    // Methods
    void spawnEnemy();
    void pollEvents();
    void updateEnemies();
    void updateMousePositions();
    void update();
    void renderEnemies();
    void render();
};

#endif