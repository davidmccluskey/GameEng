#pragma once
#include "cmp_actor_movement.h"
class PlayerMovementComponent : public ActorMovementComponent
{
private:
	int _health;
	float _shotTimer;
	float _flickerTimer = 0.1;
	bool _flicker = true;
	bool _invuln = false;
public:
	PlayerMovementComponent() = delete;
	explicit PlayerMovementComponent(Entity *p);
	void update(double dt) override;
	void addHealth();
	void removeHealth();
	void setHealth(int health);
	int getHealth();
	void switchSprite();
	void setShot(float shotTimer);
	bool getInvuln();
};