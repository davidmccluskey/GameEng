//player.h
#pragma once
#include "ecm.h"
#include "scene.h"
extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

//class Pacman : public Entity {
// private:
//  float _speed;
//
// public:
//  void update(double dt) override;
//  Pacman();
//  void render() const override;
//};

class MenuScene : public Scene {
private:
    sf::Text text;

public:
    MenuScene() = default;
    void update(double dt) override;
    void render() override;
    void load()override;
};

//pacman.h
class GameScene : public Scene {
private:
    sf::Text text;
    sf::Clock scoreClock;
    void respawn();

public:
    GameScene() = default;
    void update(double dt) override;
    void render() override;
    void load() override;
};