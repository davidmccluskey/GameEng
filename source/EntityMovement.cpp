//"cmp_actor_movement.cpp"
#include "EntityMovement.h"
#include "PlayerMovementComponent.h"
#include <iostream>
#include "SpriteComponent.h"
using namespace sf;

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
    : _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
	return 0;
}

void ActorMovementComponent::rotate(float x) {
    auto pp = _parent->getRotation();
	auto sprite = _parent->get_components<SpriteComponent>()[0];
	sprite->getSprite().rotate(x);	
	sprite->getSprite().setTextureRect(IntRect(1600, 0, 1600, 1600));
	_parent->setRotation(x);
	std::cerr << _parent->getRotation() << std::endl;
}

float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) { _speed = speed;}