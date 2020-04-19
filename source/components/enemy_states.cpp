//enemy_states.cpp
#include "enemy_states.h"
#include "cmp_sprite.h"
#include "cmp_ai_steering.h"
#include "cmp_bullet.h"
#include "../game.h"
using namespace std;
using namespace sf;
//sf::Texture sprite;
//sf::Sprite bulletSprite;

void FarState::execute(Entity *owner, double dt) noexcept {
    auto s = owner->get_components<SpriteComponent>()[0];
	//s->getSprite().setColor(sf::Color::Red);
    	
	//Change to idle if the player is closer than 450 units away
    if (length(owner->getPosition() - _player->getPosition()) < 350.0f){
        auto sm = owner->get_components<StateMachineComponent>()[0];
        sm->changeState("idle");
		//cout << "change to idle from far" << endl;
    }
}

void NearState::execute(Entity *owner, double dt) noexcept {
	auto s = owner->get_components<SpriteComponent>()[0];
	//s->getSprite().setColor(sf::Color::Yellow);
    
	//Change to idle if the player is between 200 - 450 units away
    if (length(owner->getPosition() - _player->getPosition()) < 400.0f && length(owner->getPosition() - _player->getPosition()) > 250.0f){
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("idle");
		//cout << "change to idle from near" << endl;
    }
}

void IdleState::execute(Entity *owner, double dt) noexcept {
	auto s = owner->get_components<SpriteComponent>()[0];
	//s->getSprite().setColor(sf::Color::Blue);
	
	
	//TODO
	//Shoot after some random time
	
	_fireDelay -= dt;
	if (_fireDelay <= 0) {
		float random = rand() % 100 + 1;
		if (random == 100) {
			//FIRE
			cout << "FIRE BULLET" << endl;
			_fireDelay = 4;

			auto bullet = owner->scene->makeEntity();
			bullet->addTag("enemyBullet");
			bullet->setPosition(owner->getPosition());
			auto b = bullet->addComponent<BulletComponent>();
			b->setDamage(1);
			auto s = bullet->addComponent<ShapeComponent>(); //Adds sprite component
			s->setShape<sf::CircleShape>(8.f);
			s->getShape().setFillColor(Color::Red);
			s->getShape().setOrigin(8.f, 8.f);
			//bulletSprite.setTexture(sprite);
			//bulletSprite.setScale({ 0.1f * _size, 0.1f * _size });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
			//bulletSprite.setOrigin({ 200, 200 });   //sets center of bullet
			//bulletSprite.setPosition(_parent->getPosition());   //sets position of sprite to be same as object
			//s->setSprite<Sprite>(bulletSprite);
			auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f), constENEMYBULLET, (short)(constPLAYER | constWALL), &bullet);
			p->setRestitution(.4f);
			p->setFriction(.005f);
			Vector2f impulse = sf::rotate(Vector2f(0, 50.f), -owner->get_components<SpriteComponent>()[0]->getSprite().getRotation());
			impulse = Vector2f(impulse.x , impulse.y);
			p->impulse(impulse);
		}
	}
	//Change to far if the player is more than 450 units away
	if (length(owner->getPosition() - _player->getPosition()) > 400.0f) {
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("seek");
		//cout << "change to far from idle" << endl;
	}
	//Change to near if the player is closer than 200 units away
	if (length(owner->getPosition() - _player->getPosition()) < 200.01f) {
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("flee");
		//cout << "change to near from idle" << endl;
	}
}