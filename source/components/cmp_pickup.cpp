#include "cmp_pickup.h"
#include "cmp_sprite.h"
using namespace std;
using namespace sf;
// Constructor

PickupComponent::PickupComponent(Entity* p) : Component(p)
{
}

void PickupComponent::update(double dt) {
	_timer -= dt;
	if (_timer <= 2) {
		_flickerTimer -= dt;
		if (_flicker == true) {
			if (_flickerTimer < 0) {
				auto pickupSprite = _parent->get_components<SpriteComponent>()[0];
				pickupSprite->getSprite().setColor(sf::Color::Transparent);
				_flickerTimer = 0.1;
				_flicker = false;
			}
		}
		else if (_flicker == false) {
			if (_flickerTimer < 0) {
				auto pickupSprite = _parent->get_components<SpriteComponent>()[0];
				pickupSprite->getSprite().setColor(sf::Color::White);
				_flickerTimer = 0.1;
				_flicker = true;
			}
		}
	}

	if (_timer <= 0) {
		_parent->setForDelete();
	}
}

void PickupComponent::render()
{
}
