#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class EnemyComponent : public Component {
protected:
    float _speed;
    float _damage;
    float _health;
    float _shotTimer;
    float _flickerTimer = 0.1;
    bool _flicker = true;

public:
    void update(double dt) override;
    void render() override {}
    explicit EnemyComponent(Entity* p, float speed = 1.0f, float damage = 1.0f, float health = 1.0f);
    EnemyComponent() = delete;
    
    float getHealth();
    void setHealth(float health);
    void setShot(float shotTimer);
};