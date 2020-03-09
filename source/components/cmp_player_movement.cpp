#include "cmp_player_movement.h"
#include <SFML/Window/Keyboard.hpp>
#include "cmp_bullet.h"
#include "engine.h"
#include "cmp_sprite.h"
#include "cmp_physics.h"

sf::Texture sprite;
sf::Sprite bulletSprite;
// Constructor
PlayerMovementComponent::PlayerMovementComponent(Entity* p)
    : ActorMovementComponent(p) {}
using namespace sf;
// Update
void PlayerMovementComponent::update(double dt)
{
    _firetime -= dt;
    float direction = 0.0f;
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        float x;
        x = dt * -300;
        rotate( x );
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        float x;
        x = dt * 300;
        rotate(x);
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        if (!sprite.loadFromFile("res/bullet.png")) {
            std::cerr << "Failed to load bullet!" << std::endl;
        }

        if (_firetime <= 0.f) {
            auto playerSprite = _parent->get_components<SpriteComponent>()[0];

            auto bullet = _parent->scene->makeEntity();
            bullet->setPosition(_parent->getPosition());
            bullet->addComponent<BulletComponent>();
            auto s = bullet->addComponent<SpriteComponent>();

            bulletSprite.setTexture(sprite);
            bulletSprite.setScale({ 0.1f, 0.1f });
            bulletSprite.setOrigin({200, 200});
            s->setSprite<Sprite>(bulletSprite);
            auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(10.f, 10.f));
            p->setRestitution(.4f);
            p->setFriction(.005f);
            p->impulse(sf::rotate(Vector2f(0, 15.f), playerSprite->getSprite().getRotation()));
			_firetime = 0.5;
        }
		move(dt, 400.f);
		

    }
}