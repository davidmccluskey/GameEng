#pragma once
#include "cmp_player_fire.h"
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include "cmp_sprite.h"
#include "cmp_bullet.h"
#include "cmp_actor_movement.h"
#include "system_physics.h"
#include "cmp_physics.h"
#include "../game.h"
#include <random>
#include "cmp_physics.h"
#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Audio\Sound.hpp>
#include "../options.h"
#include "../sounds.h"
#include "../texture.h"

using namespace sf;
using namespace std;
sf::Sprite bulletSprite;

PlayerFireComponent::PlayerFireComponent(Entity* p) : Component(p)
{
}
// Update
void PlayerFireComponent::update(double dt)
{
	_firetime -= dt; //Firetime set later, allows us to control weapon cooldown 

	auto playerSprite = _parent->get_components<SpriteComponent>()[0];
	float rotation = playerSprite->getSprite().getRotation();

	if (_burst == true) {
		_burstTime -= dt;
		if (_burstTime <= 0) {
			if (Options::instance()->effectsOn == true) {
				Sounds::instance()->playBlaster();
			}
			auto playerPhysics = _parent->get_components<PhysicsComponent>()[0];
			Vector2f impulse = sf::rotate(Vector2f(0, 5.f), playerSprite->getSprite().getRotation());
			impulse = Vector2f(-impulse.x * _impulse, impulse.y * _impulse);
			playerPhysics->impulse(impulse);
			fireNormal(rotation);
			_burstTime = 0.1;
			_burstNum--;
		}
	}
	if (_burstNum == 0) {
		_burst = false;
		_burstNum = 3;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(Options::instance()->shootKey)) || sf::Joystick::isButtonPressed(0, 1)) {
		if (_firetime <= 0.f) {
			if (Options::instance()->effectsOn == true) {
				Sounds::instance()->playBlaster();
			}
			//Firetime reduces everytime update is called, once  it is 0 the player can fire another bullet
			auto playerPhysics = _parent->get_components<PhysicsComponent>()[0];
			Vector2f impulse = sf::rotate(Vector2f(0, 5.f), playerSprite->getSprite().getRotation());
			impulse = Vector2f(-impulse.x * _impulse, impulse.y * _impulse);
			playerPhysics->impulse(impulse);

			switch (_bulletType) {
			case 'S':
				fireShotgun(rotation);
				break;
			case 'U':
				fireBurst(rotation);
				break;
			case 'T':
				fireTriple(rotation);
				break;
			default:
				fireNormal(rotation);
				break;
			}
			_firetime = _fireRate;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Num1)) {
		setAsNormal();
	}
	if (Keyboard::isKeyPressed(Keyboard::Num2)) {
		setAsHeavy();
	}
	if (Keyboard::isKeyPressed(Keyboard::Num3)) {
		setAsTriple();
	}
	if (Keyboard::isKeyPressed(Keyboard::Num4)) {
		setAsBurst();
	}
	if (Keyboard::isKeyPressed(Keyboard::Num5)) {
		setAsShotgun();
	}
	if (Keyboard::isKeyPressed(Keyboard::Num6)) {
		setAsQuick();
	}
}

void PlayerFireComponent::fireBurst(float rotation) {
	_burst = true;
}

void PlayerFireComponent::fireShotgun(float rotation) {

	for (int i = 0; i < 5; i++) {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);
		std::uniform_int_distribution<int> spacingGen(-5, 5);
		std::uniform_real_distribution<float> speedGen(1, 2);

		int spacing = spacingGen(generator);
		float speed = speedGen(generator);
		auto playerSprite = _parent->get_components<SpriteComponent>()[0];
		auto bullet = _parent->scene->makeEntity();
		bullet->addTag("bullet");
		bullet->setPosition(_parent->getPosition());
		auto b = bullet->addComponent<BulletComponent>();
		float inverse = fmod((rotation + 180.f), 360);  //Sets rotation of bullet to be inverse of ship rotation, using fancy maths.
		b->setDamage(_damage);
		auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
		bulletSprite.setTexture(Textures::instance()->getBulletSheet());
		bulletSprite.setScale({ 0.3f * _size, 0.3f * _size });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
		bulletSprite.setOrigin({ 200, 200 });   //sets center of bullet
		bulletSprite.setPosition(_parent->getPosition());   //sets position of sprite to be same as object
		s->setSprite<Sprite>(bulletSprite);
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f), constBULLET, (short)(constENEMY | constWALL), &bullet);
		p->setRestitution(.4f);
		p->setFriction(.005f);
		Vector2f impulse = sf::rotate(Vector2f(0, 50.f), -playerSprite->getSprite().getRotation());
		impulse = Vector2f(-impulse.x + spacing, -impulse.y + spacing);
		p->impulse(impulse * speed);

		bullet->setRotation(-spacing);

	}
}

void PlayerFireComponent::fireTriple(float rotation) {
	int angle = -10;
	for (int i = 0; i < 3; i++) {
		auto playerSprite = _parent->get_components<SpriteComponent>()[0];
		auto bullet = _parent->scene->makeEntity();
		bullet->addTag("bullet");
		bullet->setPosition(_parent->getPosition());
		auto b = bullet->addComponent<BulletComponent>();
		b->setDamage(_damage);
		auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
		bulletSprite.setTexture(Textures::instance()->getBulletSheet());
		bulletSprite.setScale({ 0.3f * _size, 0.3f * _size });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
		bulletSprite.setOrigin({ 200, 200 });   //sets center of bullet
		bulletSprite.setPosition(_parent->getPosition());   //sets position of sprite to be same as object
		s->setSprite<Sprite>(bulletSprite);
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f), constBULLET, (short)(constENEMY | constWALL), &bullet);
		p->setRestitution(.4f);
		p->setFriction(.005f);
		Vector2f impulse = sf::rotate(Vector2f(0, 50.f), -playerSprite->getSprite().getRotation() + angle);
		impulse = Vector2f(-impulse.x * _bulletSpeed, -impulse.y * _bulletSpeed);
		p->impulse(impulse);
		angle += 10;
	}

}
void PlayerFireComponent::fireNormal(float rotation) {
	auto playerSprite = _parent->get_components<SpriteComponent>()[0];
	auto bullet = _parent->scene->makeEntity();
	bullet->addTag("bullet");
	bullet->setPosition(_parent->getPosition());
	auto b = bullet->addComponent<BulletComponent>();
	b->setDamage(_damage);
	auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
	bulletSprite.setTexture(Textures::instance()->getBulletSheet());
	bulletSprite.setTextureRect(IntRect(600, 0, 200, 200));
	bulletSprite.setOrigin(100, 100);
	bulletSprite.setScale({ 0.3f * _size, 0.3f * _size });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
	bulletSprite.setPosition(_parent->getPosition());   //sets position of sprite to be same as object
	s->setSprite<Sprite>(bulletSprite);
	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f), constBULLET, (short)(constENEMY | constWALL), &bullet);
	p->setRestitution(.4f);
	p->setFriction(.005f);
	Vector2f impulse = sf::rotate(Vector2f(0, 50.f), -playerSprite->getSprite().getRotation());
	impulse = Vector2f(-impulse.x * _bulletSpeed, -impulse.y * _bulletSpeed);
	p->impulse(impulse);
}

void PlayerFireComponent::render() {} //empty required method


void PlayerFireComponent::setAsNormal()
{
	_bulletType = 'D';
	_fireRate = 0.6;
	_impulse = 2;
	_damage = 2;
	_size = 1;
	_bulletSpeed = 0.9;

	_firetime = 0;

}
void PlayerFireComponent::setAsHeavy()
{
	_bulletType = 'H';
	_impulse = 6;
	_fireRate = 1.2;
	_damage = 7;
	_size = 2.5;
	_bulletSpeed = 0.4;

	_firetime = 0;

}

void PlayerFireComponent::setAsTriple()
{
	_bulletType = 'T';
	_fireRate = 0.6;
	_impulse = 2;
	_damage = 2;
	_size = 1.2;
	_bulletSpeed = 0.9;

	_firetime = 0;
}





void PlayerFireComponent::setAsQuick()
{
	_bulletType = 'Q';
	_fireRate = 0.1;
	_impulse = 0.5;
	_damage = 0.5;
	_size = 0.5;
	_bulletSpeed = 1.5;

	_firetime = 0;

}

void PlayerFireComponent::setAsShotgun()
{
	_bulletType = 'S';
	_fireRate = 0.8;
	_impulse = 4;
	_damage = 2;
	_size = 1;

	_firetime = 0;

}

void PlayerFireComponent::setAsBurst()
{
	_bulletType = 'U';
	_fireRate = 0.8;
	_impulse = 0.8;
	_damage = 2;
	_size = 1;
	_bulletSpeed = 1.5;

	_firetime = 0;

}



