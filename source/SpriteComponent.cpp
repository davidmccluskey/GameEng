#include "SpriteComponent.h"
#include "Renderer.h"

// Constructor

void SpriteComponent::update(double dt) {
    _sprite->setPosition(_parent->getPosition());
}

void SpriteComponent::render() { Renderer::queue(_sprite.get()); }

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }

SpriteComponent::SpriteComponent(Entity* p) : Component(p), _sprite(std::make_shared<sf::Sprite>()) {}