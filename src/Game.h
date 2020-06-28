#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <sstream>

class Game
{
private:
    // Window
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videoMode;

    // Mouse Position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Game Logic
    unsigned points;
    int health;
    bool endGame;

    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;

    bool mouseHeld;

    // Resources
    sf::Font font;

    // Text
    sf::Text uiText;

    // Enemy
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    // Private Methods
    void initWindow();
    void initVariables();
    void initEnemies();
    void initFonts();
    void initText();

public:
    // Constructors / Destructors
    Game(/* args */);
    virtual ~Game();

    // Accessors
    const bool running() const;
    const bool getEndGame() const;

    // Methods
    void spawnEnemy();
    void pollEvents();

    void updateText();
    void updateEnemies();
    void updateMousePositions();
    void update();

    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();
};

#endif