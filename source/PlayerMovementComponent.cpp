#include "PlayerMovementComponent.h"

// Constructor
PlayerMovementComponent::PlayerMovementComponent(Entity* p)
    : ActorMovementComponent(p) {}
using namespace sf;
// Update
void PlayerMovementComponent::update(double dt)
{
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
        move(dt);
    }
}