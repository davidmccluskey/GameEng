#pragma once
#include "cmp_player_fire.h"
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include "cmp_sprite.h"
#include "cmp_bullet_base.h"
#include "cmp_actor_movement.h"
#include "system_physics.h"
#include "cmp_physics.h"
#include "../game.h"
#include <random>

using namespace sf;
using namespace std;
sf::Texture sprite;
sf::Sprite bulletSprite;
Texture beamSprite;
Sprite beam;


PlayerFireComponent::PlayerFireComponent(Entity* p) : Component(p)
{
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
			auto playerPhysics = _parent->get_components<PhysicsComponent>()[0];
			//playerPhysics->setFriction(0.1f);
			playerPhysics->setMass(50.0f);
			playerPhysics->setTimer();
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
	sf::View currentView = Engine::GetWindow().getView();
	float leftCheck = playerSprite->getSprite().getPosition().x - (currentView.getSize().x / 2);
	float rightCheck = playerSprite->getSprite().getPosition().x + (currentView.getSize().x / 2);

	float topCheck = playerSprite->getSprite().getPosition().y - ((currentView.getSize().y / 2));

	float bottomCheck = playerSprite->getSprite().getPosition().y + ((currentView.getSize().y / 2));

	if (leftCheck >= 0 && rightCheck <= (gameWidth * scale)) {
		currentView.setCenter(playerSprite->getSprite().getPosition().x, currentView.getCenter().y);
	}
	if (topCheck >= 0 && bottomCheck <= (gameHeight * scale)) {
		currentView.setCenter(currentView.getCenter().x, playerSprite->getSprite().getPosition().y);
	}

	Engine::GetWindow().setView(currentView);
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		if (_firetime <= 0.f) {
			//Firetime reduces everytime update is called, once  it is 0 the player can fire another bullet
			auto playerPhysics = _parent->get_components<PhysicsComponent>()[0];
			//playerPhysics->setFriction(0.1f);
			playerPhysics->setMass(50.0f);
			playerPhysics->setTimer();
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
		srand(time(0) + i * 10);

		float distro = rand() % 100 + 1;
		auto bullet = _parent->scene->makeEntity();
		cout << distro << endl;
		bullet->setPosition({ _parent->getPosition().x + distro, _parent->getPosition().y + distro});    //Sets bullet position to player position
		auto b = bullet->addComponent<BaseBulletComponent>(); //Adds bullet component which determines bullet pickup
		auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
		b->setSpeed(1000 * _speed);
		bulletSprite.setTexture(sprite);
		bulletSprite.setScale({ 0.1f * distro/20, 0.1f * distro/20 });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
		bulletSprite.setOrigin({ 200, 200 });   //sets center of bullet
		bulletSprite.setPosition(bullet->getPosition());   //sets position of sprite to be same as object
		s->setSprite<Sprite>(bulletSprite);
		float inverse = fmod((rotation + 180.f), 360);  //Sets rotation of bullet to be inverse of ship rotation, using fancy maths.
		bullet->setRotation(inverse);
	}
}

void PlayerFireComponent::fireBeam(float rotation) {
	auto bullet = _parent->scene->makeEntity();
	bullet->setPosition(_parent->getPosition());    //Sets bullet position to player position
	auto b = bullet->addComponent<BaseBulletComponent>(); //Adds bullet component which determines bullet pickup
	auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
	b->setSpeed(1000 * _speed);
	b->setType('B');
	beam.setTexture(beamSprite);
	beam.setScale({ 0.1f * _size, 0.1f * _size });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
	beam.setOrigin({ 200, 880 });   //sets center of bullet
	beam.setPosition(_parent->getPosition());
	float inverse = fmod((rotation + 180.f), 360);  //Sets rotation of bullet to be inverse of ship rotation, using fancy maths.
	bullet->setRotation(inverse);
	beam.setRotation(inverse);
	s->setSprite<Sprite>(beam);
}
void PlayerFireComponent::fireTriple(float rotation) {
	int angle = -10;
	for (int i = 0; i < 3; i++) {
		auto bullet = _parent->scene->makeEntity();
		bullet->setPosition(_parent->getPosition());    //Sets bullet position to player position
		auto b = bullet->addComponent<BaseBulletComponent>(); //Adds bullet component which determines bullet pickup
		auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
		b->setSpeed(1000 * _speed);
		bulletSprite.setTexture(sprite);
		bulletSprite.setScale({ 0.1f * _size, 0.1f * _size });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
		bulletSprite.setOrigin({ 200, 200 });   //sets center of bullet
		bulletSprite.setPosition(_parent->getPosition());   //sets position of sprite to be same as object
		s->setSprite<Sprite>(bulletSprite);
		float inverse = fmod((rotation + 180.f), 360);  //Sets rotation of bullet to be inverse of ship rotation, using fancy maths.
		bullet->setRotation(inverse + (angle));
		angle += 10;
	}

}
void PlayerFireComponent::fireNormal(float rotation) {
	auto bullet = _parent->scene->makeEntity();
	bullet->setPosition(_parent->getPosition());    //Sets bullet position to player position
	auto b = bullet->addComponent<BaseBulletComponent>(); //Adds bullet component which determines bullet pickup
	auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
	b->setSpeed(1000 * _speed);
	bulletSprite.setTexture(sprite);
	bulletSprite.setScale({ 0.1f * _size, 0.1f * _size });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
	bulletSprite.setOrigin({ 200, 200 });   //sets center of bullet
	bulletSprite.setPosition(_parent->getPosition());   //sets position of sprite to be same as object
	s->setSprite<Sprite>(bulletSprite);
	float inverse = fmod((rotation + 180.f), 360);  //Sets rotation of bullet to be inverse of ship rotation, using fancy maths.
	bullet->setRotation(inverse);
}

void PlayerFireComponent::render() {} //empty required method

void PlayerFireComponent::setAsTriple()
{
	_bulletType = 'T';
	_fireRate = 1.5;
	_impulse = 2;
	_speed = 1;
	_damage = 1;
	_size = 1.5;
}

void PlayerFireComponent::setAsHeavy()
{
	_bulletType = 'H';
	_impulse = 3;
	_fireRate = 1;
	_speed = 0.5;
	_damage = 5;
	_size = 3;
}

void PlayerFireComponent::setAsBeam()
{
	_bulletType = 'B';
	_fireRate = 0.5;
	_impulse = 1;
	_speed = 1;
	_damage = 1;
	_size = 3;
}

void PlayerFireComponent::setAsNormal()
{
	_bulletType = 'D';
	_fireRate = 0.3;
	_impulse = 1;
	_speed = 1;
	_damage = 1;
	_size = 1;
}

void PlayerFireComponent::setAsQuick()
{
	_bulletType = 'Q';
	_fireRate = 0.1;
	_impulse = 0.5;
	_speed = 2;
	_damage = 1;
	_size = 0.5;
}

void PlayerFireComponent::setAsShotgun()
{
	_bulletType = 'S';
	_fireRate = 0.3;
	_impulse = 1;
	_speed = 1;
	_damage = 1;
	_size = 1;
}

void PlayerFireComponent::setAsBurst()
{
	_bulletType = 'U';
	_fireRate = 0.7;
	_impulse = 1;
	_speed = 1;
	_damage = 1;
	_size = 1;
}



