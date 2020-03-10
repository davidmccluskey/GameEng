#include "cmp_player_movement.h"
#include <SFML/Window/Keyboard.hpp>
#include "cmp_bullet.h"
#include "engine.h"
#include "cmp_sprite.h"
#include "cmp_physics.h"

// Constructor
PlayerMovementComponent::PlayerMovementComponent(Entity* p)
    : ActorMovementComponent(p) {}
using namespace sf;
// Update
void PlayerMovementComponent::update(double dt)
{
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        rotate(dt * -300); //Rotates ship left at speed of 300
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        rotate(dt * 300); //Rotates ship right at speed of 300
    }
}