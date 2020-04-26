#include "cmp_base_enemy.h"
#include "engine.h"
#include "cmp_state_machine.h"
#include "enemy_states.h"
#include "../game.h"
#include "cmp_pickup.h"
#pragma once
using namespace std;

sf::Texture pickupTex; //Player spritesheet
sf::Sprite pickupSprite; //Player sprite

void EnemyComponent::update(double dt)
{
	if (_health <= 0) {
		if (pickupTex.loadFromFile("res/pickups.png")) {
			float dropChance = rand() % 10 + 1;
			//dropChance = 10;
			if (dropChance == 10) {
				int drop = rand() % 6 + 1;
				auto pickup = _parent->scene->makeEntity();
				pickup->addComponent<PickupComponent>();
				pickup->setPosition(_parent->getPosition());

				auto s = pickup->addComponent<SpriteComponent>(); //Adds sprite component for sprite and animation handling
				auto phys = pickup->addComponent<PhysicsComponent>(true, sf::Vector2f(20,20), constPICKUP, (short)(constPLAYER), &pickup);
				pickup->setPosition(_parent->getPosition());
				pickupSprite.setTexture(pickupTex);
				s->setSprite<sf::Sprite>(pickupSprite);
				s->getSprite().setScale(0.3, 0.3);
				auto rect = sf::IntRect(200, 0, 200, 200);

				switch (drop) {
				case 1:
					rect = sf::IntRect(0, 0, 200, 200);
					s->getSprite().setTextureRect(rect);
					pickup->addTag("triple");
					break;
				case 2:
					rect = sf::IntRect(200, 0, 200, 200);
					s->getSprite().setTextureRect(rect);
					pickup->addTag("heavy");
					break;
				case 3:
					rect = sf::IntRect(400, 0, 200, 200);
					s->getSprite().setTextureRect(rect);
					pickup->addTag("quick");
					break;
				case 4:
					rect = sf::IntRect(600, 0, 200, 200);
					s->getSprite().setTextureRect(rect);
					pickup->addTag("burst");
					break;
				case 5:
					rect = sf::IntRect(800, 0, 200, 200);
					s->getSprite().setTextureRect(rect);
					pickup->addTag("shotgun");
					break;
				case 6:
					rect = sf::IntRect(1000, 0, 200, 200);
					s->getSprite().setTextureRect(rect);
					pickup->addTag("health");
					break;
				}
				s->getSprite().setOrigin({ 100,100 });
			}

		}
		score.setScore(500);
		_enemyNum--;
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
	: Component(p), _speed(speed), _damage(damage), _health(health) {

	auto player = _parent->scene->ents.find("player");
	auto sm = _parent->addComponent<StateMachineComponent>();
	sm->addState("idle", make_shared<IdleState>(player[0]));
	sm->addState("flee", make_shared<NearState>(player[0]));
	sm->addState("seek", make_shared<FarState>(player[0]));
	sm->addState("rush", make_shared<RushState>(player[0]));
	sm->changeState("idle");

}

int EnemyComponent::getTextureWidth()
{
	return textureWidth;
}

int EnemyComponent::getTextureHeight()
{
	return textureHeight;
}

int EnemyComponent::getTexturePos()
{
	return texturePos;
}
void EnemyComponent::setTextureSize(int width, int height, int pos)
{
	textureWidth = width;
	textureHeight = height;
	texturePos = pos;
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

void EnemyComponent::setMinMax(float min, float max) {
	_min = min;
	_max = max;
}

float EnemyComponent::getMin() {
	return _min;
}

float EnemyComponent::getMax() {
	return _max;
}

void EnemyComponent::setFireDelay(float value) {
	_fireDelay = value;
}

float EnemyComponent::getFireDelay() {
	return _fireDelay;
}