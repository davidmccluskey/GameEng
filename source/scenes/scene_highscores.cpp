#include "scene_highscores.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void HighScoreScene::Load() {
  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Dummy high score screen, press space to return");
  }
  setLoaded(true);
}

void HighScoreScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

    if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
        Engine::ChangeScene(&menu);
    }

  Scene::Update(dt);
}
