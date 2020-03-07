#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Gun Thrusters\nPress 1 for game\nPress 2 for highs scores\nPress 3 for settings\nPress 4 to exit game");
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

    if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
        Engine::ChangeScene(&scene_main);
    }
    else if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
        Engine::ChangeScene(&scene_highscores);
    }
    else if (sf::Keyboard::isKeyPressed(Keyboard::Num3)) {
        Engine::ChangeScene(&scene_settings);
    }
    else if (sf::Keyboard::isKeyPressed(Keyboard::Num4)) {
        exit(EXIT_FAILURE);
    }

  Scene::Update(dt);
}
