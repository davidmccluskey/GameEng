#include "cmp_physics.h"
#include "system_physics.h"
#include "cmp_bullet.h"
#include "cmp_base_enemy.h"
#include "cmp_player_fire.h"
#include "cmp_player_movement.h"
#include "../game.h"
#include "cmp_player_movement.h"
#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Audio\Sound.hpp>
#include "../options.h"
#include "../sounds.h"
using namespace std;
using namespace sf;

using namespace Physics;
void PhysicsComponent::update(double dt) {
	
	_parent->setPosition(bv2_to_sv2(_body->GetPosition()));

	auto tagSet = _parent->getTags();
		string parentTag = tagSet.begin()->c_str();
	if (parentTag == "enemy" || parentTag == "player") {
		double deg = (double)(3.14159265359 / 180);
		auto s = _parent->get_components<SpriteComponent>()[0];
		_body->SetTransform(sv2_to_bv2(_parent->getPosition()), s->getSprite().getRotation()*deg);
	}

	
	

}

PhysicsComponent::PhysicsComponent(Entity* p, bool dyn,
	const Vector2f& size, short cBits, short mBits, void* userdata)
	: Component(p), _dynamic(dyn) {

	b2BodyDef BodyDef;
	// Is Dynamic(moving), or static(Stationary)
	BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;
	BodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));

	// Create the body
	_body = Physics::GetWorld()->CreateBody(&BodyDef);
	_body->SetActive(true);
	{
		// Create the fixture shape
		b2PolygonShape Shape;
		// SetAsBox box takes HALF-Widths!
		Shape.SetAsBox(sv2_to_bv2(size).x, sv2_to_bv2(size).y);
		b2FixtureDef FixtureDef;
		// Fixture properties
		// FixtureDef.density = _dynamic ? 10.f : 0.f;
		FixtureDef.friction = _dynamic ? 0.1f : 0.8f;
		FixtureDef.restitution = .2;
		FixtureDef.shape = &Shape;

		FixtureDef.filter.categoryBits = cBits;
		FixtureDef.filter.maskBits = mBits;
		_body->SetUserData(this);
		// Add to body
		_fixture = _body->CreateFixture(&FixtureDef);
		//_fixture->SetRestitution(.9)
		FixtureDef.restitution = .2;
	}
}

void PhysicsComponent::setFriction(float r) { _fixture->SetFriction(r); }

void PhysicsComponent::collisionResponse(void* collider) {
	PhysicsComponent* c = static_cast<PhysicsComponent*>(collider);
	auto child = c->_parent;
	auto tagSet = _parent->getTags();
	string parentTag = tagSet.begin()->c_str();
	tagSet = child->getTags();
	string childTag = tagSet.begin()->c_str();
	if (parentTag == "enemy" && childTag == "enemy") {
		return;
	}
	if ((parentTag == "bullet" && childTag == "enemy")) {
		if (Options::instance()->effectsOn == true) {
			Sounds::instance()->playEnemyHit();
		}
		score.setScore(50);
		auto bullet = _parent->get_components<BulletComponent>()[0];
		auto enemy = child->get_components<EnemyComponent>()[0];
		float damage = bullet->getDamage();
		enemy->setShot(1);
		enemy->setHealth(enemy->getHealth() - damage);
		_parent->setForDelete();
	}
	if (parentTag == "shotgun" && childTag == "player") {
		_parent->setForDelete();
		auto fire = child->get_components<PlayerFireComponent>()[0];
		score.setScore(100);
		fire->setAsShotgun();
	}
	if (parentTag == "burst" && childTag == "player") {
		_parent->setForDelete();
		auto fire = child->get_components<PlayerFireComponent>()[0];
		score.setScore(100);
		fire->setAsBurst();
	}
	if (parentTag == "triple" && childTag == "player") {
		_parent->setForDelete();
		auto fire = child->get_components<PlayerFireComponent>()[0];
		score.setScore(100);
		fire->setAsTriple();
	}
	if (parentTag == "quick" && childTag == "player") {
		_parent->setForDelete();
		auto fire = child->get_components<PlayerFireComponent>()[0];
		score.setScore(100);
		fire->setAsQuick();
	}
	if (parentTag == "heavy" && childTag == "player") {
		_parent->setForDelete();
		auto fire = child->get_components<PlayerFireComponent>()[0];
		score.setScore(100);
		fire->setAsHeavy();
	}
	if (parentTag == "health" && childTag == "player") {
		_parent->setForDelete();
		score.setScore(100);
		auto p = child->get_components<PlayerMovementComponent>()[0];
		p->addHealth();
		p->switchSprite();		
	}
	if (parentTag == "enemyBullet" && childTag == "player") {
		_parent->setForDelete();
		screenshake = true;
		shakeTimer = 0.5;
		if (Options::instance()->effectsOn == true) {
			Sounds::instance()->playPlayerHit();
		}
		auto p = child->get_components<PlayerMovementComponent>()[0];
		if (p->getInvuln() == false) {
			p->setShot(1);
			p->removeHealth();
			p->switchSprite();
		}
	}
	if (parentTag == "enemy" && childTag == "player") {
		if (Options::instance()->effectsOn == true) {
			Sounds::instance()->playEnemyHit();
		}
		score.setScore(50);
		auto enemy = _parent->get_components<EnemyComponent>()[0];
		enemy->setShot(1);

		auto tags = _parent->getTags();

		std::set<std::string>::iterator tag = tags.begin();
		std::advance(tag, 1);
		if (*tag != "spike") {
			float collisionDamage = length(getVelocity()) * 0.03;
			cout << "Collison Damage: " << collisionDamage << endl;
			enemy->setHealth(enemy->getHealth() - collisionDamage);
		}
		
		if (Options::instance()->effectsOn == true) {
			Sounds::instance()->playPlayerHit();
		}
		auto p = child->get_components<PlayerMovementComponent>()[0];
		if (p->getInvuln() == false) {
			p->setShot(1);
			p->removeHealth();
			p->switchSprite();
		}
		
	}
}

void PhysicsComponent::setMass(float m) { _fixture->SetDensity(m); }

void PhysicsComponent::teleport(const sf::Vector2f& v) {
	_body->SetTransform(sv2_to_bv2(invert_height(v)), 0.0f);
}

const sf::Vector2f PhysicsComponent::getVelocity() const {
	return bv2_to_sv2(_body->GetLinearVelocity(), true);
}
void PhysicsComponent::setVelocity(const sf::Vector2f& v) {
	_body->SetLinearVelocity(sv2_to_bv2(v, true));
}

b2Fixture* const PhysicsComponent::getFixture() const { return _fixture; }

PhysicsComponent::~PhysicsComponent() {
	auto a = Physics::GetWorld();
	_body->SetActive(false);
	Physics::GetWorld()->DestroyBody(_body);
	// delete _body;
	_body = nullptr;
}

void PhysicsComponent::render() {}

void PhysicsComponent::impulse(const sf::Vector2f& i) {
	auto a = b2Vec2(i.x, i.y * -1.0f);
	_body->ApplyLinearImpulseToCenter(a, true);
}

void PhysicsComponent::dampen(const sf::Vector2f& i) {
	auto vel = _body->GetLinearVelocity();
	vel.x *= i.x;
	vel.y *= i.y;
	_body->SetLinearVelocity(vel);
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc) const {
	b2Contact* bc;
	return isTouching(pc, bc);
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc,
	b2Contact const* bc) const {
	const auto _otherFixture = pc.getFixture();
	const auto& w = *Physics::GetWorld();
	const auto contactList = w.GetContactList();
	const auto clc = w.GetContactCount();
	for (int32 i = 0; i < clc; i++) {
		const auto& contact = (contactList[i]);
		if (contact.IsTouching() && ((contact.GetFixtureA() == _fixture &&
			contact.GetFixtureA() == _otherFixture) ||
			(contact.GetFixtureA() == _otherFixture &&
				contact.GetFixtureA() == _fixture))) {
			bc = &contact;
			return true;
		}
	}
	return false;
}

std::vector<const b2Contact const*> PhysicsComponent::getTouching() const {
	std::vector<const b2Contact const*> ret;

	b2ContactEdge* edge = _body->GetContactList();
	while (edge != NULL) {
		const b2Contact* contact = edge->contact;
		if (contact->IsTouching()) {
			ret.push_back(contact);
		}
		edge = edge->next;
	}

	return ret;
}

void PhysicsComponent::setRestitution(float r) {
	_fixture->SetRestitution(r);
}

b2Body* PhysicsComponent::getBody() {
	return _body;
}

