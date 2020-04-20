#include "scene_enter_score.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_menu.h"

using namespace std;
using namespace sf;

void SettingsScreen::Load() {
    auto back = makeEntity();
    back->addTag("back");

    back->setPosition({ gameWidth * 0.15, gameHeight * 0.1});

    auto s = back->addComponent<MenuItemComponent>("Back");

  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Dummy settings screen, Press SPACE to return");
  }
  setLoaded(true);
}

void SettingsScreen::Update(const double& dt) {
    clickCooldown -= dt;
  // cout << "Menu Update "<<dt<<"\n";
    sf::Event event;
    RenderWindow& window = Engine::GetWindow();
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
    }

    if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
        Engine::ChangeScene(&menu);
    }

  Scene::Update(dt);
}
