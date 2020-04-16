#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class BulletComponent : public Component {
protected:
  float _lifetime;
  float _size;
  float _impulse;
  float _speed;
  float _damage;

public:
  void update(double dt) override;
  void render() override {}
  void setDamage(float damage);
  explicit BulletComponent(Entity* p, float lifetime = 1.0f, float size = 1.f, float impulse = 1.f, float speed = 1.f, float damage = 1.f);
  BulletComponent() = delete;

  float getDamage();
};
