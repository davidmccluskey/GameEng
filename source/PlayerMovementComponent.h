#pragma once
#include "EntityMovement.h"
class PlayerMovementComponent : public ActorMovementComponent
{
public:
	PlayerMovementComponent() = delete;
	explicit PlayerMovementComponent(Entity *p);

	void update(double dt) override;
};