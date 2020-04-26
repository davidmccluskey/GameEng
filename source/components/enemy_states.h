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
	float _fireDelay = 1;
	std::shared_ptr<Entity> _player;
public:
	IdleState(std::shared_ptr<Entity> player) : _player(player) { }
	void execute(Entity*, double) noexcept override;
};

class RushState : public State
{
private:
	float _rushDelay = 2;
	float _timer = 2;
	std::shared_ptr<Entity> _player;
public:
	RushState(std::shared_ptr<Entity> player) : _player(player) { }
	void execute(Entity*, double) noexcept override;
};