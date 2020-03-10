#pragma once
#include "cmp_player_fire.h"
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include "cmp_sprite.h"
#include "cmp_bullet_base.h"
#include "cmp_actor_movement.h"
#include "system_physics.h"

sf::Texture sprite;
sf::Sprite bulletSprite;

using namespace sf;
using namespace std;

PlayerFireComponent::PlayerFireComponent(Entity* p) : Component(p)
{
}
// Update
void PlayerFireComponent::update(double dt)
{
    _firetime -= dt;
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        if (!sprite.loadFromFile("res/bullet.png")) {
            std::cerr << "Failed to load bullet!" << std::endl;
        }

        if (_firetime <= 0.f) {
            auto playerSprite = _parent->get_components<SpriteComponent>()[0];
            float rotation = playerSprite->getSprite().getRotation();
            auto bullet = _parent->scene->makeEntity();
            bullet->setPosition(_parent->getPosition());
            bullet->addComponent<BaseBulletComponent>();
            auto s = bullet->addComponent<SpriteComponent>();

            bulletSprite.setTexture(sprite);
            bulletSprite.setScale({ 0.1f, 0.1f });
            bulletSprite.setOrigin({ 200, 200 });
            bulletSprite.setPosition(_parent->getPosition());
            s->setSprite<Sprite>(bulletSprite);
            float inverse = fmod((rotation + 180.f), 360);
            bulletSprite.setRotation(inverse);
            bullet->setRotation(inverse);

            _firetime = 0.5f;
            cout << rotation << endl;
        }
        move(dt, (300.f));
    }
}

void PlayerFireComponent::render() {}

void PlayerFireComponent::move(double dt, float impulse)
{
    float floatDT = (float)dt;

    auto sprite = _parent->get_components<SpriteComponent>()[0];
    float rotation = sprite->getSprite().getRotation();
    float angleRADS = (3.1415926536 / -180) * ((rotation - 90));

    float forx = (floatDT * impulse) * cos(angleRADS);
    float fory = (floatDT * impulse) * -sin(angleRADS);
    Vector2f spritePosition = sprite->getSprite().getPosition();

    float moveX = (spritePosition.x + forx);
    float moveY = (spritePosition.y + fory);
    sprite->getSprite().setPosition({ moveX, moveY });
    _parent->setPosition({ (moveX), (moveY) });
    sf::View currentView = Engine::GetWindow().getView();
    currentView.setCenter(sprite->getSprite().getPosition().x, sprite->getSprite().getPosition().y);
    Engine::GetWindow().setView(currentView);
}
