#pragma once
#include <ecm.h>

class BaseBulletComponent : public Component {
protected:
    float _lifetime;
    float _speed;
    char _type;

public:
    void update(double dt) override;
    void render() override {}
    explicit BaseBulletComponent(Entity* p, float lifetime = 3.f, float speed = 500);
    BaseBulletComponent() = delete;

    float getSpeed();
    void setSpeed(float speed);

    char getType();
    void setType(char type);
};
