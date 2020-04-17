#include "cmp_base_enemy.h"

#pragma once

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
				enemySprite->getSprite().setColor(sf::Color::Red);
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
	: Component(p), _speed(speed), _damage(damage), _health(health) {}


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
