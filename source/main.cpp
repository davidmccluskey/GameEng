#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "game.h"
#include "GunThruster.h"
#include "Renderer.h"
using namespace sf;
using namespace std;

sf::Texture backgroundTexture;
sf::Sprite background;
sf::CircleShape shape(100.f);

void Load() {
    // Load Scene-Local Assets
    menuScene.reset(new MenuScene());
    gameScene.reset(new GameScene());

    menuScene->load();
    gameScene->load();
    // Start at main menu
    activeScene = menuScene;
}

void Render(RenderWindow& window)
{
    activeScene->render();
    Renderer::render();
    //cout << "Render called" << endl;

}

void Update(RenderWindow& window)
{
    static Clock clock;
    float dt = clock.restart().asSeconds();
    activeScene->update(dt);
    //cout << "Update called" << endl;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Space Game!");
    Renderer::initialise(window);
    Load();
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
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}


