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
    float forx = (floatDT * 300) * cos(angleRADS);
    float fory = (floatDT * 300) * -sin(angleRADS);
    Vector2f spritePosition = sprite->getSprite().getPosition();
    cout << rotation << endl;
    float moveX = (spritePosition.x + forx);
    float moveY = (spritePosition.y + fory);
    sprite->getSprite().setPosition({ moveX, moveY });
    _parent->setPosition({ (moveX), (moveY) });
}

BaseBulletComponent::BaseBulletComponent(Entity* p, float lifetime, float impulse, float speed, float damage, float size)
    : Component(p), _lifetime(lifetime), _impulse(impulse), _speed(speed) {}