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
}