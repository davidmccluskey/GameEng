#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML\Window\Mouse.hpp>
#include <system_renderer.h>
#include "../components/cmp_sprite.h"

using namespace std;
using namespace sf;

Texture background;
Sprite spriteBackground;
Texture textureMenu;
Sprite spriteMenu;
void MenuScene::Load() {
  cout << "Menu Load \n";
  if (background.loadFromFile("res/background.jpeg")) {
      spriteBackground.setTexture(background);
      spriteBackground.setPosition(0, 0);
  }
  {
      if (textureMenu.loadFromFile("res/menu-item.png")) {
          spriteMenu.setTexture(textureMenu);
          auto start = makeEntity();
          auto highscore = makeEntity();
          auto options = makeEntity();
          auto exit = makeEntity();

          auto s = start->addComponent<SpriteComponent>();
          auto h = highscore->addComponent<SpriteComponent>();
          auto o = options->addComponent<SpriteComponent>();
          auto e = exit->addComponent<SpriteComponent>();

          s->setSprite<Sprite>(spriteMenu);
          start->setPosition({ 250, gameHeight * 0.40});
          s->getSprite().setOrigin(200,50);
          auto startText = makeEntity();
          auto st = startText->addComponent<TextComponent>("Start");
          st->SetPosition({ 150, gameHeight * 0.35 });
          st->SetSize(60);
          st->SetColour(sf::Color::Red);

          h->setSprite<Sprite>(spriteMenu);
          highscore->setPosition({ 250, gameHeight * 0.55 });
          h->getSprite().setOrigin(200, 50);

          o->setSprite<Sprite>(spriteMenu);
          options->setPosition({ 250, gameHeight * 0.70 });
          o->getSprite().setOrigin(200, 50);


          e->setSprite<Sprite>(spriteMenu);
          exit->setPosition({ 250, gameHeight * 0.85 });
          e->getSprite().setOrigin(200, 50);
      }
      {
          auto txt = makeEntity();
          auto t = txt->addComponent<TextComponent>("Gunthrusters");
          t->SetPosition({ 70, gameHeight * 0.10 });
          t->SetSize(60);
          t->SetColour(sf::Color::Red);
      }
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";
    static bool mouse_down = false;
            auto mouse_pos = Mouse::getPosition(Engine::GetWindow());

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
    if (sf::Mouse::isButtonPressed(Mouse::Left) && !mouse_down) {
        auto mouse_pos = Mouse::getPosition(Engine::GetWindow());
        mouse_down = true;
        cout << mouse_pos << endl;
    }
    if (mouse_down && !Mouse::isButtonPressed(Mouse::Left)) {
        mouse_down = false;
    }

  Scene::Update(dt);
}

void MenuScene::Render()
{
    Renderer::queue(&spriteBackground);
    Scene::Render();
}
