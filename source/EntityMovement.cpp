//"cmp_actor_movement.cpp"
#include "EntityMovement.h"
#include "PlayerMovementComponent.h"
#include <iostream>
#include "SpriteComponent.h"
#include "maths.h"
#include "Renderer.h"
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
void ActorMovementComponent::move(double dt){
	auto sprite = _parent->get_components<SpriteComponent>()[0];
	float rotation = sprite->getSprite().getRotation();
	float angleRADS = (3.1415926536 / -180) * ((rotation - 90));

	//Set x and y
	float forx = 0.4f * cos(angleRADS);
	float fory = 0.4f * -sin(angleRADS);
	Vector2f spritePosition = sprite->getSprite().getPosition();

	float moveX = spritePosition.x + forx;
	float moveY = spritePosition.y + fory;
	sprite->getSprite().setPosition({moveX, moveY});
	//sprite->getSprite().setPosition({ 500, 500 });
	_parent->setPosition({ (spritePosition.x + forx) , (spritePosition.y + fory) });
	//TODO: MULTIPLY BY DT
	sf:: View currentView = Renderer::getWindow().getView();
	currentView.setCenter(sprite->getSprite().getPosition().x, sprite->getSprite().getPosition().y);
	Renderer::getWindow().setView(currentView);
}
float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) { _speed = speed;}