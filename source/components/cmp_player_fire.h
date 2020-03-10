#pragma once
#include <ecm.h>

class PlayerFireComponent : public Component
{
private:
	float _firetime;
public:
	PlayerFireComponent() = delete;
	explicit PlayerFireComponent(Entity* p);

	void update(double dt) override;
	void render() override;
	void move(double dt, float impulse);
};