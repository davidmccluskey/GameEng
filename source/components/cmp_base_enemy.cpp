#include "cmp_base_enemy.h"
#include "engine.h"
#include "cmp_state_machine.h"
#include "enemy_states.h"
#pragma once
using namespace std;

void EnemyComponent::update(double dt)
{
	if (_health <= 0) {
		_parent->setForDelete();
	}
	if (_shotTimer > 0) {
		_shotTimer -= dt;
		_flickerTimer -= dt;

		if (_flicker == true) {
			if (_flickerTimer < 0) {
				auto enemySprite = _parent->get_components<SpriteComponent>()[0];
				enemySprite->getSprite().setColor(sf::Color::Transparent);
				_flickerTimer = 0.1;
				_flicker = false;
			}
		} else if (_flicker == false) {
			if (_flickerTimer < 0) {
				auto enemySprite = _parent->get_components<SpriteComponent>()[0];
				enemySprite->getSprite().setColor(sf::Color::White);
				_flickerTimer = 0.1;
				_flicker = true;
			}
		}
	}
	else if (_shotTimer < 0) {
		_shotTimer = 0;
		auto enemySprite = _parent->get_components<SpriteComponent>()[0];
		enemySprite->getSprite().setColor(sf::Color::White);
	}
}

EnemyComponent::EnemyComponent(Entity* p, float speed, float damage, float health)
	: Component(p), _speed(speed), _damage(damage), _health(health) {

	auto player = _parent->scene->ents.find("player");
	auto sm = _parent->addComponent<StateMachineComponent>();
	sm->addState("normal", make_shared<NormalState>(player[0]));
	sm->addState("near", make_shared<NearState>(player[0]));
	sm->changeState("normal");

}


float EnemyComponent::getHealth()
{
	return _health;
}

void EnemyComponent::setHealth(float health)
{
	_health = health;
}

void EnemyComponent::setShot(float shotTimer)
{
	_shotTimer = shotTimer;
}
