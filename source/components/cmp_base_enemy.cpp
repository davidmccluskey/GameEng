#include "cmp_base_enemy.h"

#pragma once

void EnemyComponent::update(double dt)
{
	if (_health <= 0) {
		_parent->setForDelete();
	}
}

EnemyComponent::EnemyComponent(Entity* p, float speed, float damage, float health)
	: Component(p), _speed(speed), _damage(damage), _health(health){}


float EnemyComponent::getHealth()
{
	return _health;
}

void EnemyComponent::setHealth(float health)
{
	_health = health;
}
