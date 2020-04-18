//enemy_states.cpp
#include "enemy_states.h"
#include "cmp_sprite.h"

using namespace sf;

void NormalState::execute(Entity *owner, double dt) noexcept {
    auto s = owner->get_components<SpriteComponent>()[0];
	//s->getSprite().setColor(sf::Color::White);
    
    if (length(owner->getPosition() - _player->getPosition()) < 100.0f){
        auto sm = owner->get_components<StateMachineComponent>()[0];
        sm->changeState("near");
    }
}

void NearState::execute(Entity *owner, double dt) noexcept {
    auto s = owner->get_components<SpriteComponent>()[0];
	s->getSprite().setColor(sf::Color::Yellow);
    
    if (length(owner->getPosition() - _player->getPosition()) > 100.0f){
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("normal");
    }
}
