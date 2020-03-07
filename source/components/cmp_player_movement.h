#pragma once
#include "cmp_actor_movement.h"
class PlayerMovementComponent : public ActorMovementComponent
{
private:
	float _firetime;
public:
	PlayerMovementComponent() = delete;
	explicit PlayerMovementComponent(Entity *p);

	void update(double dt) override;
};