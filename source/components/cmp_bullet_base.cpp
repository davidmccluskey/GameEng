#include "cmp_bullet_base.h"
#include "cmp_sprite.h"
using namespace std;
using namespace sf;

void BaseBulletComponent::update(double dt) {
    _lifetime -= dt;
    if (_lifetime <= 0.f) {
        _parent->setForDelete();
    }
    float floatDT = (float)dt;
    auto sprite = _parent->get_components<SpriteComponent>()[0];
    float rotation = _parent->getRotation();
    float angleRADS = (3.1415926536 / -180) * ((rotation - 90));
    float forx = (floatDT * _speed) * cos(angleRADS);
    float fory = (floatDT * _speed) * -sin(angleRADS);
    Vector2f spritePosition = sprite->getSprite().getPosition();
    float moveX = (spritePosition.x + forx);
    float moveY = (spritePosition.y + fory);
    sprite->getSprite().setPosition({ moveX, moveY });
    _parent->setPosition({ (moveX), (moveY) });
}

BaseBulletComponent::BaseBulletComponent(Entity* p, float lifetime, float impulse, float speed, float damage, float size, float frate)
    : Component(p), _lifetime(lifetime), _impulse(impulse), _speed(speed), _fireRate(frate) {}

float BaseBulletComponent::getSpeed() {
    return _speed;
}

float BaseBulletComponent::getFRate() {
    return _fireRate;
}
