#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "game.h"

using namespace sf;
using namespace std;

sf::Texture backgroundTexture;
sf::Sprite background;
sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Space Game!");
sf::CircleShape shape(100.f);

void Load() 
{

}

void Render() 
{
    window.draw(background);
}

void Update(float dt)
{
}
int main() {

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
        
            }
        }
        window.clear();
        Load();
        Render();
        window.display();
    }
    return 0;
}


