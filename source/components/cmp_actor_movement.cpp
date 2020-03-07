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
	sprite->getSprite().setTextureRect(IntRect(1600, 0, 1600, 1600));
	_parent->setRotation(x);
	//std::cerr << _parent->getRotation() << std::endl;
}
void ActorMovementComponent::move(double dt, float impulse){
	float floatDT = (float)dt;

	auto sprite = _parent->get_components<SpriteComponent>()[0];
	float rotation = sprite->getSprite().getRotation();
	float angleRADS = (3.1415926536 / -180) * ((rotation - 90));

	//Set x and y
	float forx = (floatDT * impulse) * cos(angleRADS);
	float fory = (floatDT * impulse) * -sin(angleRADS);
	Vector2f spritePosition = sprite->getSprite().getPosition();

	float moveX = (spritePosition.x + forx);
	float moveY = (spritePosition.y + fory);
	sprite->getSprite().setPosition({moveX, moveY});
	_parent->setPosition({(moveX), (moveY)});
	//TODO: MULTIPLY BY DT
	sf::View currentView = Engine::GetWindow().getView();
	currentView.setCenter(sprite->getSprite().getPosition().x, sprite->getSprite().getPosition().y);
	Engine::GetWindow().setView(currentView);
	//std::cerr << _parent->getRotation() << std::endl;
	//std::cerr << dt << std::endl;

}
float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) { _speed = speed;}