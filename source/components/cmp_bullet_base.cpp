#include "cmp_bullet_base.h"
#include "cmp_sprite.h"
using namespace std;
using namespace sf;

void BaseBulletComponent::update(double dt) {
    std::set<string>::iterator it;
    auto sprite = _parent->get_components<SpriteComponent>()[0];
    _lifetime -= dt;
    if (_lifetime <= 0.f) {
        _parent->setForDelete(); //If bullet is on screen too long it should be deleted
    }
    if (_type != 'B') {
        float floatDT = (float)dt;
        float rotation = _parent->getRotation();
        float angleRADS = (3.1415926536 / -180) * ((rotation - 90));
        float forx = (floatDT * _speed) * cos(angleRADS);
        float fory = (floatDT * _speed) * -sin(angleRADS);
        Vector2f spritePosition = sprite->getSprite().getPosition();
        float moveX = (spritePosition.x + forx);
        float moveY = (spritePosition.y + fory);
        sprite->getSprite().setPosition({ moveX, moveY });
        _parent->setPosition({ (moveX), (moveY) }); //Similar to player movement code but for bullet, maths and logic is the same 
    }
    else {
    }

}

BaseBulletComponent::BaseBulletComponent(Entity* p, float lifetime,float speed)
    : Component(p), _lifetime(lifetime), _speed(speed){}

float BaseBulletComponent::getSpeed() {
    return _speed;
}

void BaseBulletComponent::setSpeed(float speed) {
    _speed = speed;
}

char BaseBulletComponent::getType()
{
	return _type;
}

void BaseBulletComponent::setType(char type)
{
    _type = type;
}




