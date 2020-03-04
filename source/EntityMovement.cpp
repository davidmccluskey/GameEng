//"cmp_actor_movement.cpp"
#include "EntityMovement.h"
#include "PlayerMovementComponent.h"
#include <iostream>
using namespace sf;

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
    : _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
	return 0;
}

void ActorMovementComponent::rotate(float x) {
    auto pp = _parent->getRotation();
	_parent->setRotation(x);
	_parent->get_components<PlayerMovementComponent>();
	std::cerr << _parent->getRotation() << std::endl;
}

float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) { _speed = speed;}