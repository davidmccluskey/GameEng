//enemy_states.cpp
#include "enemy_states.h"
#include "cmp_sprite.h"
#include "cmp_ai_steering.h"
#include "cmp_bullet.h"
#include "cmp_base_enemy.h"
#include "../game.h"
#include "cmp_base_enemy.h"
#include "../texture.h"
#include <random>
using namespace std;
using namespace sf;
sf::Sprite enemyBulletSprite;
//sf::Sprite bulletSprite;

void FarState::execute(Entity* owner, double dt) noexcept {
	auto s = owner->get_components<SpriteComponent>()[0];
	auto e = owner->get_components<EnemyComponent>()[0];
	float max = e->getMax();
	IntRect rect = s->getSprite().getTextureRect();

	_animationFrames -= dt;
	if (_animationFrames < 0) {
		rect.left = e->getTextureWidth() * currentFrame;
		currentFrame++;
		if (currentFrame == 5) {
			currentFrame = 0;
		}
		_animationFrames = 0.05;
	}

	s->getSprite().setTextureRect(rect);
	//Change to idle if the player is closer than 450 units away
	if (length(owner->getPosition() - _player->getPosition()) < max - 50) {
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("idle");
		//cout << "change to idle from far" << endl;
	}
}

void NearState::execute(Entity* owner, double dt) noexcept {
	auto s = owner->get_components<SpriteComponent>()[0];
	auto e = owner->get_components<EnemyComponent>()[0];
	float max = e->getMax();
	float min = e->getMin();
	IntRect rect = s->getSprite().getTextureRect();
	rect.left = e->getTextureWidth() * 6;

	s->getSprite().setTextureRect(rect);

	//Change to idle if the player is between 200 - 450 units away
	if (length(owner->getPosition() - _player->getPosition()) < max && length(owner->getPosition() - _player->getPosition()) > min + 50) {
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("idle");
		//cout << "change to idle from near" << endl;
	}
}

void IdleState::execute(Entity* owner, double dt) noexcept {
	auto s = owner->get_components<SpriteComponent>()[0];
	//s->getSprite().setColor(sf::Color::Blue);

	auto e = owner->get_components<EnemyComponent>()[0];
	float min = e->getMin();
	float max = e->getMax();

	IntRect rect = s->getSprite().getTextureRect();
	rect.left = e->getTextureWidth() * 6;

	s->getSprite().setTextureRect(rect);



	auto tags = owner->getTags();

	std::set<std::string>::iterator tag = tags.begin();
	std::advance(tag, 1);
	if (*tag == "spike") {
		//TODO
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("rush");
	}
	else {
		_fireDelay -= dt;
		if (_fireDelay <= 0) {
			float random = rand() % 100 + 1;
			//cout << random << endl;
			if (random == 100) {
				if (*tag == "orb" || *tag == "harpoon" || *tag == "small")
				{
					Fire(owner, dt);
				}
				else if (*tag == "finalBoss") {
					int attack = rand() % 3 + 1;
					switch (attack) {
					case 1:
						BossAttackOne(owner, dt);
						break;
					case 2:
						BossAttackTwo(owner, dt);
						break;
					case 3:
						BossAttackThree(owner, dt);
						break;
					}
				}
			}
		}
	}
	//Change to far if the player is more than 450 units away
	if (length(owner->getPosition() - _player->getPosition()) > max + (max - min / 2)) {
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("seek");
		//cout << "change to far from idle" << endl;
	}
	//Change to near if the player is closer than 200 units away
	//if (length(owner->getPosition() - _player->getPosition()) < min) {
	//	auto sm = owner->get_components<StateMachineComponent>()[0];
	//	sm->changeState("flee");
	//	//cout << "change to near from idle" << endl;
	//}
}

void IdleState::Fire(Entity* owner, double dt) {
	//FIRE
	auto e = owner->get_components<EnemyComponent>()[0];
	//cout << "FIRE BULLET" << endl;
	_fireDelay = e->getFireDelay();
	auto bullet = owner->scene->makeEntity();
	bullet->addTag("enemyBullet");
	bullet->setPosition(owner->getPosition());
	auto b = bullet->addComponent<BulletComponent>();
	b->setDamage(1);
	auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
	enemyBulletSprite.setTexture(Textures::instance()->getBulletSheet());
	s->setSprite<Sprite>(enemyBulletSprite);
	auto ownerSprite = owner->get_components<SpriteComponent>()[0];

	auto tags = owner->getTags();

	std::set<std::string>::iterator tag = tags.begin();
	std::advance(tag, 1);
	if (*tag == "harpoon") {
		s->getSprite().setTextureRect(IntRect(200, 0, 200, 200));
		s->getSprite().setOrigin(100, 100);
		s->getSprite().setScale(0.3, 0.3);
	}
	else if (*tag == "orb") {
		s->getSprite().setTextureRect(IntRect(0, 0, 200, 200));
		s->getSprite().setOrigin(100, 100);
		s->getSprite().setScale(0.2, 0.2);

	}
	else if (*tag == "small") {
		s->getSprite().setTextureRect(IntRect(400, 0, 200, 200));
		s->getSprite().setScale(0.15, 0.15);
	}

	s->getSprite().setOrigin(100, 100);
	s->getSprite().setRotation(ownerSprite->getSprite().getRotation());
	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f), constENEMYBULLET, (short)(constPLAYER | constWALL), &bullet);
	p->setRestitution(.4f);
	p->setFriction(.005f);
	Vector2f impulse = sf::rotate(Vector2f(0, 50.f), -owner->get_components<SpriteComponent>()[0]->getSprite().getRotation());
	impulse = Vector2f(impulse.x * 0.5, impulse.y * 0.5);
	p->impulse(impulse);
}

void IdleState::BossAttackOne(Entity* owner, double dt) {
	int angle = -20;
	auto e = owner->get_components<EnemyComponent>()[0];
	//cout << "FIRE BULLET" << endl;
	_fireDelay = 1.5;
	for (int i = 0; i < 3; i++) {
		auto bullet = owner->scene->makeEntity();
		bullet->addTag("enemyBullet");
		bullet->setPosition(owner->getPosition());
		auto b = bullet->addComponent<BulletComponent>();
		b->setDamage(1);
		auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
		enemyBulletSprite.setTexture(Textures::instance()->getBulletSheet());
		s->setSprite<Sprite>(enemyBulletSprite);
		auto ownerSprite = owner->get_components<SpriteComponent>()[0];

		auto tags = owner->getTags();

		std::set<std::string>::iterator tag = tags.begin();
		std::advance(tag, 1);

		s->getSprite().setTextureRect(IntRect(400, 0, 200, 200));
		s->getSprite().setScale(0.5, 0.5);
		s->getSprite().setOrigin(100, 100);
		s->getSprite().setRotation(ownerSprite->getSprite().getRotation() - angle);
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f), constENEMYBULLET, (short)(constPLAYER | constWALL), &bullet);
		p->setRestitution(.4f);
		p->setFriction(.005f);
		Vector2f impulse = sf::rotate(Vector2f(0, 50.f), -owner->get_components<SpriteComponent>()[0]->getSprite().getRotation() + angle);
		impulse = Vector2f(impulse.x * 0.3, impulse.y * 0.3);
		p->impulse(impulse);
		angle += 20;
	}
}
void IdleState::BossAttackTwo(Entity* owner, double dt) {
	for (int i = 0; i < 5; i++) {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);
		std::uniform_int_distribution<int> spacingGen(-5, 5);
		//std::uniform_real_distribution<float> speedGen(1, 2);
		int spacing = spacingGen(generator);
		//float speed = speedGen(generator);
		auto e = owner->get_components<EnemyComponent>()[0];
		//cout << "FIRE BULLET" << endl;
		_fireDelay = 1.5;
		auto bullet = owner->scene->makeEntity();
		bullet->addTag("enemyBullet");
		bullet->setPosition(owner->getPosition());
		auto b = bullet->addComponent<BulletComponent>();
		b->setDamage(1);
		auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
		enemyBulletSprite.setTexture(Textures::instance()->getBulletSheet());
		s->setSprite<Sprite>(enemyBulletSprite);
		auto ownerSprite = owner->get_components<SpriteComponent>()[0];

		auto tags = owner->getTags();

		std::set<std::string>::iterator tag = tags.begin();
		std::advance(tag, 1);

		s->getSprite().setTextureRect(IntRect(400, 0, 200, 200));
		s->getSprite().setScale(0.5, 0.5);
		s->getSprite().setOrigin(100, 100);
		s->getSprite().setRotation(ownerSprite->getSprite().getRotation());
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f), constENEMYBULLET, (short)(constPLAYER | constWALL), &bullet);
		p->setRestitution(.4f);
		p->setFriction(.005f);
		Vector2f impulse = sf::rotate(Vector2f(0, 50.f), -owner->get_components<SpriteComponent>()[0]->getSprite().getRotation());
		impulse = Vector2f((impulse.x + spacing) * 0.6, (impulse.y + spacing) * 0.6);
		p->impulse(impulse);
	}
}
void IdleState::BossAttackThree(Entity* owner, double dt) {
	int angle = 0;
	for (int i = 0; i < 18; i++) {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);
		std::uniform_int_distribution<int> spacingGen(-5, 5);
		//std::uniform_real_distribution<float> speedGen(1, 2);
		int spacing = spacingGen(generator);
		//float speed = speedGen(generator);
		auto e = owner->get_components<EnemyComponent>()[0];
		//cout << "FIRE BULLET" << endl;
		_fireDelay = 1.5;
		auto bullet = owner->scene->makeEntity();
		bullet->addTag("enemyBullet");
		bullet->setPosition(owner->getPosition());
		auto b = bullet->addComponent<BulletComponent>();
		b->setDamage(1);
		auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component
		enemyBulletSprite.setTexture(Textures::instance()->getBulletSheet());
		s->setSprite<Sprite>(enemyBulletSprite);
		auto ownerSprite = owner->get_components<SpriteComponent>()[0];

		auto tags = owner->getTags();

		std::set<std::string>::iterator tag = tags.begin();
		std::advance(tag, 1);

		s->getSprite().setTextureRect(IntRect(400, 0, 200, 200));
		s->getSprite().setScale(0.5, 0.5);
		s->getSprite().setOrigin(100, 100);
		s->getSprite().setRotation(ownerSprite->getSprite().getRotation() - angle);
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f), constENEMYBULLET, (short)(constPLAYER | constWALL), &bullet);
		p->setRestitution(.4f);
		p->setFriction(.005f);
		Vector2f impulse = sf::rotate(Vector2f(0, 50.f), -owner->get_components<SpriteComponent>()[0]->getSprite().getRotation() + angle);
		impulse = Vector2f((impulse.x + spacing) * 0.2, (impulse.y + spacing) * 0.2);
		p->impulse(impulse);
		angle += 20;
	}
}

void RushState::execute(Entity* owner, double dt) noexcept {
	auto s = owner->get_components<SpriteComponent>()[0];
	auto p = owner->get_components<PhysicsComponent>()[0];
	//s->getSprite().setColor(sf::Color::Red);

	_rushDelay -= dt;
	//cout << _rushDelay << endl;
	if (_rushDelay <= 0) {
		//cout << "RUSH" << endl;
		auto point = owner->getPosition() + _player->getPosition();
		Vector2f impulse = sf::rotate(Vector2f(0, 5.f), s->getSprite().getRotation());
		impulse = Vector2f(-impulse.x * 15, impulse.y * 15);
		p->impulse(impulse);
		_rushDelay = 10;
		_timer = 2;

	}
	auto sm = owner->get_components<StateMachineComponent>()[0];
	_timer -= dt;
	if (_timer <= 0) {
		_rushDelay = 2;
		sm->changeState("idle");
		_timer = 10;
	}
}