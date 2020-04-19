//"cmp_ai_steering.cpp"
#include "cmp_ai_steering.h"
#include "cmp_sprite.h"
#include "../game.h"
#include "cmp_physics.h"
#include "cmp_state_machine.h"
#include "system_physics.h"
using namespace sf;

void SteeringComponent::update(double dt) {
	
	auto enemySprite = _parent->get_components<SpriteComponent>()[0];
	auto playerSprite = _player->get_components<SpriteComponent>()[0];

	float a = enemySprite->getSprite().getPosition().x - playerSprite->getSprite().getPosition().x;
	float b = enemySprite->getSprite().getPosition().y - playerSprite->getSprite().getPosition().y;

	float angle = -atan2(a, b) * 180 / 3.14;

	enemySprite->getSprite().setRotation(angle);

	auto enemyPhysics = _parent->get_components<PhysicsComponent>()[0];
	auto sm = _parent->get_components<StateMachineComponent>()[0];

	if (sm->currentState() == "seek") {
		auto output = _seek.getSteering();
		enemyPhysics->setVelocity(output.direction);

	}
	else if (sm->currentState() == "flee"){
		auto output = _flee.getSteering();
		enemyPhysics->setVelocity(output.direction);
	}
	else if (sm->currentState() == "idle") {
		enemyPhysics->setVelocity({0.0f,0.0f});
	}

}

SteeringComponent::SteeringComponent(Entity* p, Entity* player, float speed)
	: _player(player), _seek(Seek(p, player, speed)),
	_flee(Flee(p, player, speed)), Component(p) {}


bool SteeringComponent::validMove(const sf::Vector2f& pos) const {
	if (pos.x < 0.0f || pos.x > Engine::GetWindow().getSize().x* scale ||
		pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y * scale) {
		return false;
	}
	return true;
}

