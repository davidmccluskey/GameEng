//player.cpp
#include "SpriteComponent.h"
#include"GunThruster.h"
#include "scene.h"
#include "ecm.h"
#include "Renderer.h"
#include <iostream>
#include "PlayerMovementComponent.h"
#include "game.h"

using namespace sf;
using namespace std;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

sf::Texture spritesheet;
sf::Sprite playerSprite;

Font font;

Texture backgroundtexture;
Sprite backgroundSprite;


void Scene::update(double dt)
{
    _ents.update(dt);
}

void Scene::render() { _ents.render(); }

std::vector<std::shared_ptr<Entity>>& Scene::getEnts()
{
    return _ents.list;
}

//pacman.cpp
void MenuScene::update(double dt) {
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        activeScene = gameScene;
    }
    Scene::update(dt);
    text.setString("Menu Test");
}

void MenuScene::render() {
    Renderer::queue(&text);
    Scene::render();
}

void MenuScene::load() {
    font.loadFromFile("res/fonts/RobotoMono.ttf");
    if (!spritesheet.loadFromFile("res/SpriteSheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    if (!backgroundtexture.loadFromFile("res/background.jpeg")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    Vector2u size = backgroundtexture.getSize();
    backgroundSprite.setTexture(backgroundtexture);


    sf::Vector2u targetSize = Renderer::getWindow().getSize();

    backgroundSprite.setScale(
        targetSize.x / backgroundSprite.getLocalBounds().width,
        targetSize.y / backgroundSprite.getLocalBounds().height);
    // Set text element to use font
    text.setFont(font);
    // set the character size to 24 pixels
    text.setCharacterSize(24);
    text.setPosition(300, 300);
}
std::shared_ptr<Entity> player;
std::vector<std::shared_ptr<Entity>> ghosts;
void GameScene::load() {
    {
        player = make_shared<Entity>();
        auto s = player->addComponent<SpriteComponent>();
        auto p = player->addComponent<PlayerMovementComponent>();
        playerSprite.setTexture(spritesheet);
        p->setSpeed(100.f);
        s->setSprite<Sprite>(playerSprite);

        auto rect = IntRect(0, 0, 1600, 1600);

        s->getSprite().setTextureRect(rect);
        s->getSprite().setOrigin(800, 800);
        s->getSprite().setScale({ 0.1, 0.1 });
        player->setPosition({ 400,400 });
        _ents.list.push_back(player);
    }

    GameScene::respawn();
}

void GameScene::update(double dt) {
    if (Keyboard::isKeyPressed(Keyboard::Tab)) {
        activeScene = menuScene;
    }
    Scene::update(dt);
    //_ents.update(dt);
}

void GameScene::render()
{
    Renderer::queue(&backgroundSprite);
    Scene::render();
}

void GameScene::respawn() {

    player->GetCompatibleComponent<ActorMovementComponent>()[0]
        ->setSpeed(150.f);
}
