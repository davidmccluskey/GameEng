#pragma once
#include <ecm.h>
class PlayerFireComponent : public Component
{
private:
	float _fireRate = 0.3;
	float _firetime = 0;
	char _bulletType = 'D';
	float _impulse = 1;
	float _speed = 1;
	float _damage = 1;
	float _size = 1;

	float _bulletSpeed = 1;

	bool _burst = false;
	float _burstTime = 0.1;
	float _burstNum = 3;
public:
	PlayerFireComponent() = delete;
	explicit PlayerFireComponent(Entity* p);

	void update(double dt) override;
	void render() override;

	void setAsTriple();
	void setAsHeavy();
	void setAsNormal();

	void setAsQuick();
	void setAsShotgun();
	void setAsBurst();

	void fireBurst(float rotation);

	void fireShotgun(float rotation);

	void fireTriple(float rotation);

	void fireNormal(float rotation);

};