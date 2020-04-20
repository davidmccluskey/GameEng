#pragma once
#include "cmp_actor_movement.h"
class PlayerMovementComponent : public ActorMovementComponent
{
private:
	int _health;
public:
	float _timer = 0;
	PlayerMovementComponent() = delete;
	explicit PlayerMovementComponent(Entity *p);
	void update(double dt) override;
	void addHealth();
	void removeHealth();
	void setHealth(int health);
};