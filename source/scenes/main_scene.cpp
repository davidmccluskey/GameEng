#include "main_scene.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include "../components/cmp_text.h"
#include "../components/cmp_player_movement.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "system_renderer.h"
using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
sf::Texture spritesheet;
sf::Sprite playerSprite;

Texture backgroundtexture;
Sprite backgroundSprite;
sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f));

void MainScene::Load() {
    if (!spritesheet.loadFromFile("res/SpriteSheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    if (!backgroundtexture.loadFromFile("res/background.jpeg")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    Vector2u size = backgroundtexture.getSize();
    backgroundSprite.setTexture(backgroundtexture);

    sf::Vector2u targetSize = Engine::getWindowSize();

    backgroundSprite.setScale(
        (targetSize.x / backgroundSprite.getLocalBounds().width) * 3,
        (targetSize.y / backgroundSprite.getLocalBounds().height) * 3);
    player = makeEntity();
    player->setPosition({ 400, 400 });
    auto s = player->addComponent<SpriteComponent>();
    auto p = player->addComponent<PlayerMovementComponent>();
    playerSprite.setTexture(spritesheet);
    p->setSpeed(100.f);
    s->setSprite<Sprite>(playerSprite);

    auto rect = IntRect(0, 0, 1600, 1600);

    s->getSprite().setTextureRect(rect);
    s->getSprite().setOrigin(800, 800);
    s->getSprite().setScale({ 0.05, 0.05 });
    player->setPosition({ 400,400 });



  //Simulate long loading times UNCOMMENT FOR RELEASE
  //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  //cout << " Main scene Load Done" << endl;
  view.setSize(1200.f, 800.f);
  view.zoom(1.0f);
  view.setCenter(400, 400);
  Engine::GetWindow().setView(view);
  setLoaded(true);
}

void MainScene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player.reset();
  Scene::UnLoad();
}

void MainScene::Update(const double& dt) {
  Scene::Update(dt);
}

void MainScene::Render() {
  Renderer::queue(&backgroundSprite);
  Scene::Render();
}
