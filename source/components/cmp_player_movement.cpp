#include "cmp_player_movement.h"
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include "cmp_sprite.h"
#include "cmp_physics.h"
#include <random>
#include "cmp_player_fire.h"
#include "cmp_bullet_base.h"
#include <SFML/Window/Joystick.hpp>
#include "../game.h"
// Constructor
PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: ActorMovementComponent(p) {
	_health = 4;
}
using namespace sf;
using namespace std;

// Update
void PlayerMovementComponent::update(double dt)
{
	cout << _invuln << endl;	
	if (_shotTimer > 0) {
		_shotTimer -= dt;
		_flickerTimer -= dt;
		_invuln = true;

		if (_flicker == true) {
			if (_flickerTimer < 0) {
				auto enemySprite = _parent->get_components<SpriteComponent>()[0];
				enemySprite->getSprite().setColor(sf::Color::Red);
				_flickerTimer = 0.1;
				_flicker = false;
			}
		}
		else if (_flicker == false) {
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
		_invuln = false;
	}
	if (_health <= 0) {
		Engine::ChangeScene(&scene_enter_highscore);
		return;
	}
	else {
		auto p = _parent->get_components<PhysicsComponent>()[0];
		Vector2f vel = p->getVelocity();
		float deceleration = -0.4 * (dt * dt) - dt + 1;
		p->setVelocity(Vector2f(vel.x * deceleration, vel.y * deceleration));

		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

		if (x < -20) {
			rotate(dt * (x * 3));
		}
		else if (x > 20) {
			rotate(dt * (x * 3));
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			rotate(dt * -400); //Rotates ship left at speed of 300
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			rotate(dt * 400); //Rotates ship right at speed of 300
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			removeHealth();
			cout << _health << endl;
		}
	}
}

void PlayerMovementComponent::addHealth()
{
	if (_health == 4) {
		return;
	}
	else {
		_health++;
	}
}

void PlayerMovementComponent::removeHealth()
{

	_health--;

}

void PlayerMovementComponent::setHealth(int health)
{
	_health = health;
}

int PlayerMovementComponent::getHealth() {
	return _health;
}

void PlayerMovementComponent::switchSprite() {
	auto s = _parent->get_components<SpriteComponent>()[0];
	switch (_health) {
	case 4:
		s->getSprite().setTextureRect(IntRect(0, 0, 1600, 1600));
		break;
	case 3:
		s->getSprite().setTextureRect(IntRect(1600, 0, 1600, 1600));
		break;
	case 2:
		s->getSprite().setTextureRect(IntRect(3200, 0, 1600, 1600));
		break;
	case 1:
		s->getSprite().setTextureRect(IntRect(4800, 0, 1600, 1600));
		break;
	case 0:
		break;
	}
}
void PlayerMovementComponent::setShot(float shotTimer)
{
	_shotTimer = shotTimer;
}

bool PlayerMovementComponent::getInvuln()
{
	return _invuln;
}
