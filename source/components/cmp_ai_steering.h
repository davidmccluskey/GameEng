//"cmp_ai_steering.h"
#pragma once
#include <ecm.h>
#include "../steering.h"

class SteeringComponent : public Component{
protected:
    Seek _seek;
    Flee _flee;
    Entity *_player;
	bool validMove(const sf::Vector2f&) const;
public:
    void update(double) override;
    void render() override { }
    explicit SteeringComponent(Entity *p, Entity *player, float speed);
    SteeringComponent() = delete;
};