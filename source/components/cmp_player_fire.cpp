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

using namespace sf;
using namespace std;
sf::Texture sprite;
sf::Sprite bulletSprite;
Texture beamSprite;
Sprite beam;
sf::SoundBuffer buffer;
sf::Sound sound;


PlayerFireComponent::PlayerFireComponent(Entity* p) : Component(p)
{
	srand(time(0));
	if (buffer.loadFromFile("res/soundFX/blaster.wav"))
	{
		cout << "sound loaded" << endl;
	}
	sprite.loadFromFile("res/bullet.png");
	beamSprite.loadFromFile("res/brimstone.png");
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
			sound.setBuffer(buffer);
			sound.setVolume(20);
			sound.play();
			auto playerPhysics = _parent->get_components<PhysicsComponent>()[0];
			//playerPhysics->setFriction(0.1f);
			//playerPhysics->setTimer();
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
	if (Keyboard::isKeyPressed(Keyboard::W) || sf::Joystick::isButtonPressed(0, 1)) {
		if (_firetime <= 0.f) {
			sound.setBuffer(buffer);
			sound.setVolume(20);
			sound.play();
			//Firetime reduces everytime update is called, once  it is 0 the player can fire another bullet
			auto playerPhysics = _parent->get_components<PhysicsComponent>()[0];
			//playerPhysics->setFriction(0.1f);
			//playerPhysics->setTimer();
			Vector2f impulse = sf::rotate(Vector2f(0, 5.f), playerSprite->getSprite().getRotation());
			impulse = Vector2f(-impulse.x * _impulse, impulse.y * _impulse);
			playerPhysics->impulse(impulse);

			switch (_bulletType) {
			case 'B':
				fireBeam(rotation);
				break;
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
		setAsBeam();
	}
	if (Keyboard::isKeyPressed(Keyboard::Num4)) {
		setAsTriple();
	}
	if (Keyboard::isKeyPressed(Keyboard::Num5)) {
		setAsBurst();
	}
	if (Keyboard::isKeyPressed(Keyboard::Num6)) {
		setAsShotgun();
	}
	if (Keyboard::isKeyPressed(Keyboard::Num7)) {
		setAsQuick();
	}
}

void PlayerFireComponent::fireBurst(float rotation) {
	_burst = true;
}

void PlayerFireComponent::fireShotgun(float rotation) {

	for (int i = 0; i < 5; i++) {

		//auto bullet = _parent->scene->makeEntity();
		float spacing = rand() % 20 + (-10);
		float speed = rand() % (30 - 5 + 1) + 5;
		//bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y});    //Sets bullet position to player position
		//auto b = bullet->addComponent<BaseBulletComponent>(); //Adds bullet component which determines bullet pickup
		//auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
		//b->setSpeed(speed);
		//bulletSprite.setTexture(sprite);
		//bulletSprite.setScale({ 0.1f, 0.1f});  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
		//bulletSprite.setOrigin({ 200, 200 });   //sets center of bullet
		//bulletSprite.setPosition(bullet->getPosition());   //sets position of sprite to be same as object
		//s->setSprite<Sprite>(bulletSprite);
		//float inverse = fmod((rotation + 180.f), 360);  //Sets rotation of bullet to be inverse of ship rotation, using fancy maths.
		//bullet->setRotation(inverse + spacing);

		auto playerSprite = _parent->get_components<SpriteComponent>()[0];
		auto bullet = _parent->scene->makeEntity();
		bullet->addTag("bullet");
		bullet->setPosition(_parent->getPosition());
		auto b = bullet->addComponent<BulletComponent>();
		float inverse = fmod((rotation + 180.f), 360);  //Sets rotation of bullet to be inverse of ship rotation, using fancy maths.
		b->setDamage(_damage);
		auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
		bulletSprite.setTexture(sprite);
		bulletSprite.setScale({ 0.1f * _size, 0.1f * _size });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
		bulletSprite.setOrigin({ 200, 200 });   //sets center of bullet
		bulletSprite.setPosition(_parent->getPosition());   //sets position of sprite to be same as object
		s->setSprite<Sprite>(bulletSprite);
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f), constBULLET, (short)(constENEMY | constWALL), &bullet);
		p->setRestitution(.4f);
		p->setFriction(.005f);
		Vector2f impulse = sf::rotate(Vector2f(0, 50.f), -playerSprite->getSprite().getRotation());
		impulse = Vector2f(-impulse.x + speed, -impulse.y + speed);
		p->impulse(impulse);

		bullet->setRotation(inverse + spacing);

	}
}

void PlayerFireComponent::fireBeam(float rotation) {
	//auto bullet = _parent->scene->makeEntity();
	//bullet->setPosition(_parent->getPosition());    //Sets bullet position to player position
	//auto b = bullet->addComponent<BaseBulletComponent>(); //Adds bullet component which determines bullet pickup
	//auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
	//b->setSpeed(1000 * _speed);
	//b->setType('B');
	//beam.setTexture(beamSprite);
	//beam.setScale({ 0.1f * _size, 0.1f * _size });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
	//beam.setOrigin({ 200, 880 });   //sets center of bullet
	//beam.setPosition(_parent->getPosition());
	//float inverse = fmod((rotation + 180.f), 360);  //Sets rotation of bullet to be inverse of ship rotation, using fancy maths.
	//bullet->setRotation(inverse);
	//beam.setRotation(inverse);
	//s->setSprite<Sprite>(beam); 
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
		bulletSprite.setTexture(sprite);
		bulletSprite.setScale({ 0.1f * _size, 0.1f * _size });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
		bulletSprite.setOrigin({ 200, 200 });   //sets center of bullet
		bulletSprite.setPosition(_parent->getPosition());   //sets position of sprite to be same as object
		s->setSprite<Sprite>(bulletSprite);
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f), constBULLET, (short)(constENEMY | constWALL), &bullet);
		p->setRestitution(.4f);
		p->setFriction(.005f);
		Vector2f impulse = sf::rotate(Vector2f(0, 50.f), -playerSprite->getSprite().getRotation() + angle);
		impulse = Vector2f(-impulse.x * _impulse, -impulse.y * _impulse);
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
	bulletSprite.setTexture(sprite);
	bulletSprite.setScale({ 0.1f * _size, 0.1f * _size });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
	bulletSprite.setOrigin({ 200, 200 });   //sets center of bullet
	bulletSprite.setPosition(_parent->getPosition());   //sets position of sprite to be same as object
	s->setSprite<Sprite>(bulletSprite);
	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f), constBULLET, (short)(constENEMY | constWALL), &bullet);
	p->setRestitution(.4f);
	p->setFriction(.005f);
	Vector2f impulse = sf::rotate(Vector2f(0, 50.f), -playerSprite->getSprite().getRotation());
	impulse = Vector2f(-impulse.x, -impulse.y);
	p->impulse(impulse);
}

void PlayerFireComponent::render() {} //empty required method

void PlayerFireComponent::setAsTriple()
{
	_bulletType = 'T';
	_fireRate = 1;
	_impulse = 2;
	_damage = 1;
	_size = 1.5;
}

void PlayerFireComponent::setAsHeavy()
{
	_bulletType = 'H';
	_impulse = 5;
	_fireRate = 1;
	_damage = 5;
	_size = 3;
}

void PlayerFireComponent::setAsBeam()
{
	_bulletType = 'B';
	_fireRate = 3.5;
	_impulse = 1;
	_damage = 1;
	_size = 3;
}

void PlayerFireComponent::setAsNormal()
{
	_bulletType = 'D';
	_fireRate = 0.3;
	_impulse = 1;
	_damage = 1;
	_size = 1;
}

void PlayerFireComponent::setAsQuick()
{
	_bulletType = 'Q';
	_fireRate = 0.1;
	_impulse = 0.5;
	_damage = 1;
	_size = 0.5;
}

void PlayerFireComponent::setAsShotgun()
{
	_bulletType = 'S';
	_fireRate = 0.3;
	_impulse = 4;
	_damage = 1;
	_size = 1;
}

void PlayerFireComponent::setAsBurst()
{
	_bulletType = 'U';
	_fireRate = 0.7;
	_impulse = 1;
	_damage = 1;
	_size = 1;
}



