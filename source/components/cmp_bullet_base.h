#pragma once
#include <ecm.h>

class BaseBulletComponent : public Component {
protected:
    float _lifetime;
    float _impulse;
    float _speed;
    float _damage;
    float _size;
    float _fireRate;
public:
    void update(double dt) override;
    void render() override {}
    explicit BaseBulletComponent(Entity* p, float lifetime = 1.f, float impulse = 1.f, float speed = 500, float damage = 1.f, float size = 1.f, float frate = 0.2f);
    BaseBulletComponent() = delete;

    float getSpeed();
    float getFRate();
};
