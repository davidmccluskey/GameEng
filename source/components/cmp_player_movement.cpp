#include "cmp_player_movement.h"
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include "cmp_sprite.h"
#include "cmp_physics.h"
#include <random>
#include "cmp_player_fire.h"
#include "cmp_bullet_base.h"
#include <SFML/Window/Joystick.hpp>
#include "../game.h"
// Constructor
PlayerMovementComponent::PlayerMovementComponent(Entity* p)
    : ActorMovementComponent(p) {
}
using namespace sf;
using namespace std;

// Update
void PlayerMovementComponent::update(double dt)
{
   

	//Old Fake Friction
	//_timer -= dt;
    //if (_timer < 0) {
    //	_timer = 0.1;
    //    auto p = _parent->get_components<PhysicsComponent>()[0];
    //	Vector2f vel = p->getVelocity();
    //	p->setVelocity(Vector2f(vel.x * 0.7, vel.y * 0.7));
    //}

	//Fake Friction
	auto p = _parent->get_components<PhysicsComponent>()[0];
	Vector2f vel = p->getVelocity();
	float deceleration = -0.4*(dt * dt) - dt + 1;
	p->setVelocity(Vector2f(vel.x * deceleration, vel.y * deceleration));

    float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

    if (x < -20) {
        rotate(dt * (x * 3));
    }
    else if (x > 20) {
        rotate(dt * (x * 3));
    }

    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        rotate(dt * -400); //Rotates ship left at speed of 300
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        rotate(dt * 400); //Rotates ship right at speed of 300
    }
}