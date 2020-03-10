//"cmp_actor_movement.cpp"
#include "cmp_actor_movement.h"
#include "cmp_player_movement.h"
#include <iostream>
#include "cmp_sprite.h"
#include "maths.h"
#include "system_renderer.h"
#include "engine.h"
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
	_parent->setRotation(x);
	//std::cerr << "parent " << _parent->getRotation() << std::endl;
	//std::cerr << "sprite " << sprite->getSprite().getRotation() << std::endl;
}
void ActorMovementComponent::move(double dt, float impulse){
	//BASE MOVEMENT FOR ENEMIES
}
float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) { _speed = speed;}