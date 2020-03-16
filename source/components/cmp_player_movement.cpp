#include "cmp_player_movement.h"
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include "cmp_sprite.h"
#include "cmp_physics.h"
#include <random>
#include "cmp_player_fire.h"
#include "cmp_bullet_base.h"
#include <SFML/Window/Joystick.hpp>


// Constructor
PlayerMovementComponent::PlayerMovementComponent(Entity* p)
    : ActorMovementComponent(p) {}
using namespace sf;
using namespace std;

// Update
void PlayerMovementComponent::update(double dt)
{
    float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

    if (x < -20) {
        rotate(dt * (x * 3));
    }
    else if (x > 20) {
        rotate(dt * (x * 3));
    }

    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        rotate(dt * -300); //Rotates ship left at speed of 300
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        rotate(dt * 300); //Rotates ship right at speed of 300
    }
}