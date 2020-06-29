#include <iostream>
#include <ctime>

#include "Game.h"

Game::Game() {
    /**
     * @brief Game constructor
     * 
     */
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
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
    this->health = 10;
    this->endGame = false;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;

    this->mouseHeld = false;
}

void Game::initFonts() {
    if(!this->font.loadFromFile("../fonts/ARCADECLASSIC.TTF")) {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load fonts\n";
    }
}

void Game::initText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

const bool Game::running() const {
    /**
     * @brief Retrun if the game is running
     * 
     */
    return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
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

    for(int i =0; i < enemies.size(); ++i) {
        this->enemies[i].move(0.f, 5.f);

        // Check if enemy has gone below the bottom
        if(this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health: " << this->health << "\n";
        }
    }

    // Check if enemy has been clicked
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(!this->mouseHeld) {
            this->mouseHeld = true;
            bool deleted = false;
            for(size_t i = 0; i < this->enemies.size() && !deleted; i++) {
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);

                    // Gain points
                    this->points += 1;
                    std::cout << "Points: " << this->points << "\n";
                }
            }
        }
    } else {
        this->mouseHeld = false;
    }
}

void Game::updateMousePositions() {
    /**
     * @brief Update the current mouse position within the window
     * 
     */
    this->mousePosWindow = sf::Mouse::getPosition(*(this->window));
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText() {
    std::stringstream ss;

    ss << "Points " << this->points << "\n"
       << "Health " << this->health;

    this->uiText.setString(ss.str());
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

    this->enemy.setSize(sf::Vector2f(1.f, 1.f));
    this->enemy.setFillColor(sf::Color::Cyan);
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

    // Randomize enemy type
    int type = rand() % 5;

    switch(type) {
        case 0:
            this->enemy.setScale(sf::Vector2f(10.f, 10.f));
            this->enemy.setFillColor(sf::Color::Magenta);
            break;
        case 1:
            this->enemy.setScale(sf::Vector2f(30.f, 30.f));
            this->enemy.setFillColor(sf::Color::Blue);
            break;
        case 2:
            this->enemy.setScale(sf::Vector2f(50.f, 50.f));
            this->enemy.setFillColor(sf::Color::Cyan);
            break;
        case 3:
            this->enemy.setScale(sf::Vector2f(70.f, 70.f));
            this->enemy.setFillColor(sf::Color::Red);
            break;
        case 4:
            this->enemy.setScale(sf::Vector2f(100.f, 100.f));
            this->enemy.setFillColor(sf::Color::Green);
            break;
        default:
            this->enemy.setScale(sf::Vector2f(100.f, 100.f));
            this->enemy.setFillColor(sf::Color::Yellow);
            break;
    }

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

    if(!this->endGame) {
        this->updateMousePositions();

        this->updateText();

        this->updateEnemies();
    }

    // End game condition
    if(this->health <= 0) {
        endGame = true;
    }
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target) {
    /**
     * @brief Draw all enemies in the screen
     * 
     */

    for(auto &e : this->enemies) {
        target.draw(e);
    }
}

void Game::render() {
    /**
     * @brief Draw the game objects
     * 
     */
    this->window->clear();

    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}