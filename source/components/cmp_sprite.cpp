#include "cmp_sprite.h"
#include "system_renderer.h"

// Constructor

void SpriteComponent::update(double dt) {
    _sprite->setPosition(_parent->getPosition());
}

void SpriteComponent::rotateSprite(double dt) {
    _sprite->setRotation(45 * dt);
}

void SpriteComponent::render() { Renderer::queue(_sprite.get()); }

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }

SpriteComponent::SpriteComponent(Entity* p) : Component(p), _sprite(std::make_shared<sf::Sprite>()) {}