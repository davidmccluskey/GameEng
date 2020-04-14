//"cmp_ai_steering.cpp"
#include "cmp_ai_steering.h"
#include "cmp_sprite.h"
#include "../game.h"
#include "cmp_physics.h"
using namespace sf;

void SteeringComponent::update(double dt) {
	auto output = _seek.getSteering();
	auto enemySprite = _parent->get_components<SpriteComponent>()[0];
	auto playerSprite = _player->get_components<SpriteComponent>()[0];

	float a = enemySprite->getSprite().getPosition().x - playerSprite->getSprite().getPosition().x;
	float b = enemySprite->getSprite().getPosition().y - playerSprite->getSprite().getPosition().y;

	float angle = -atan2(a, b) * 180 / 3.14;

	enemySprite->getSprite().setRotation(angle);

	auto enemyPhysics = _parent->get_components<PhysicsComponent>()[0];

	// If target (player) is more than 100 pixels away seek
	if (length(_parent->getPosition() - _player->getPosition()) > 300.0f) {
		//move(output.direction * (float)dt);
		float x = (output.direction.x * dt) + _parent->getPosition().x;
		float y = (output.direction.y * dt) + _parent->getPosition().y;

		enemyPhysics->teleport(Vector2f(x, y));
	}
	// If target (player) is less than 50 pixels away flee
	else if (length(_parent->getPosition() - _player->getPosition()) <
		100.0f) {
		auto output = _flee.getSteering();
		float x = (output.direction.x * dt) + _parent->getPosition().x;
		float y = (output.direction.y * dt) + _parent->getPosition().y;

		//enemyPhysics->teleport(Vector2f(x, y));
		//move(output.direction * (float)dt);
	}
}

SteeringComponent::SteeringComponent(Entity* p, Entity* player)
	: _player(player), _seek(Seek(p, player, 100.0f)),
	_flee(Flee(p, player, 100.0f)), Component(p) {}

bool SteeringComponent::validMove(const sf::Vector2f& pos) const {
	if (pos.x < 0.0f || pos.x > Engine::GetWindow().getSize().x* scale ||
		pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y * scale) {
		return false;
	}
	return true;
}

void SteeringComponent::move(const sf::Vector2f& p) {
	auto new_pos = _parent->getPosition() + p;
	if (validMove(new_pos)) {
		_parent->setPosition(new_pos);
	}
}

void SteeringComponent::move(float x, float y) { move(Vector2f(x, y)); }