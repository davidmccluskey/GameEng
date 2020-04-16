#pragma once
#include "cmp_actor_movement.h"
class PlayerMovementComponent : public ActorMovementComponent
{
private:
public:
	float _timer = 0;
	float _health = 4;
	PlayerMovementComponent() = delete;
	explicit PlayerMovementComponent(Entity *p);
	void update(double dt) override;
};