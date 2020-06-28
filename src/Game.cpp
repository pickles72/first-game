#include <iostream>
#include <ctime>

#include <Game.h>

Game::Game() {
    /**
     * @brief Game constructor
     * 
     */
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}

Game::~Game() {
    /**
     * @brief Game destructor
     * 
     */
    delete this->window;
}

void Game::initVariables() {
    /**
     * @brief Initialize game environment variables
     * 
     */
    this->window = nullptr;

    this->points = 0;
    this->enemySpawnTimerMax = 1000.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
}

const bool Game::running() const {
    /**
     * @brief Retrun if the game is running
     * 
     */
    return this->window->isOpen();
}

void Game::updateEnemies() {
    /**
     * @brief Spawn and move enemies
     * 
     */
    if(this->enemies.size() < this->maxEnemies) {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        } else {
            this->enemySpawnTimer += 1.f;
        }
    }

    for(auto &e : this->enemies) {
        e.move(0.f, 1.f);
    }
}

void Game::updateMousePositions() {
    /**
     * @brief Update the current mouse position within the window
     * 
     */
    this->mousePosWindow = sf::Mouse::getPosition(*(this->window));
}

void Game::initWindow() {
    /**
     * @brief Initialize the game window
     * 
     */
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "My First Game", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initEnemies() {
    /**
     * @brief Initialize enemy units
     * 
     */
    this->enemy.setPosition(sf::Vector2f(10.f, 10.f));

    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}

void Game::spawnEnemy() {
    /**
     * @brief Spawn an enemy and randomly position it
     * 
     */
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    this->enemy.setFillColor(sf::Color::Green);

    this->enemies.push_back(this->enemy);
}

void Game::pollEvents() {
    /**
     * @brief Poll for events
     * 
     */
    while(this->window->pollEvent(this->ev)) {
        switch(this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                break;
        }
    }
}

void Game::update() {
    /**
     * @brief Update the current game status
     * 
     */
    this->pollEvents();

    this->updateMousePositions();

    this->updateEnemies();
}

void Game::renderEnemies() {
    /**
     * @brief Draw all enemies in the screen
     * 
     */

    for(auto &e : this->enemies) {
        this->window->draw(e);
    }
}

void Game::render() {
    /**
     * @brief Draw the game objects
     * 
     */
    this->window->clear();

    this->renderEnemies();

    this->window->display();
}