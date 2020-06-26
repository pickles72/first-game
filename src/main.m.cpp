#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main(int, char**) {
    // Window
    sf::RenderWindow window(sf::VideoMode(640, 480), "My First Game", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;

    // Game loop
    while(window.isOpen()) {
        
        // Event Polling
        while(window.pollEvent(ev)) {
            switch(ev.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(ev.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    break;
            }
        }
    }


    // Update

    // Render
    window.clear(sf::Color::Blue);
    window.display();

    return 0;
}
