//enemy_states.h
#pragma once

#include "cmp_state_machine.h"

class FarState : public State
{
private:
    std::shared_ptr<Entity> _player;
	float _animationFrames = 0.2;
	int currentFrame = 0;
public:
    FarState(std::shared_ptr<Entity> player) : _player(player) { }
    void execute(Entity*, double) noexcept override;
};

class NearState : public State
{
private:
	std::shared_ptr<Entity> _player;
public:
	NearState(std::shared_ptr<Entity> player) : _player(player) { }
	void execute(Entity*, double) noexcept override;
};

class IdleState : public State
{
private:
	float _fireDelay = 4;
	std::shared_ptr<Entity> _player;
public:
	IdleState(std::shared_ptr<Entity> player) : _player(player) { }
	void execute(Entity*, double) noexcept override;
};
