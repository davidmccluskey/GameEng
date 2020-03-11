#pragma once
#include "cmp_player_fire.h"
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include "cmp_sprite.h"
#include "cmp_bullet_base.h"
#include "cmp_actor_movement.h"
#include "system_physics.h"
#include "cmp_physics.h"
#include "../game.h"

sf::Texture sprite;
sf::Sprite bulletSprite;

using namespace sf;
using namespace std;

PlayerFireComponent::PlayerFireComponent(Entity* p) : Component(p)
{
}
// Update
void PlayerFireComponent::update(double dt)
{
    _firetime -= dt; //Firetime set later, allows us to control weapon cooldown 
    auto playerSprite = _parent->get_components<SpriteComponent>()[0];

    sf::View currentView = Engine::GetWindow().getView();
    float leftCheck = playerSprite->getSprite().getPosition().x - (currentView.getSize().x / 2);
    float rightCheck = playerSprite->getSprite().getPosition().x + (currentView.getSize().x / 2);

    float topCheck = playerSprite->getSprite().getPosition().y - ((currentView.getSize().y / 2));

    float bottomCheck = playerSprite->getSprite().getPosition().y + ((currentView.getSize().y / 2));
    
    if (leftCheck >= 0 && rightCheck <= (gameWidth * scale) ) {
        currentView.setCenter(playerSprite->getSprite().getPosition().x, currentView.getCenter().y);
    }
    if (topCheck >= 0 && bottomCheck <= (gameHeight * scale)) {
        currentView.setCenter(currentView.getCenter().x, playerSprite->getSprite().getPosition().y);
    }

    
	Engine::GetWindow().setView(currentView);
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        if (!sprite.loadFromFile("res/bullet.png")) {
            std::cerr << "Failed to load bullet!" << std::endl; //CHANGE LATER SHOULD NOT LOAD EVERY FRAME
        }

        if (_firetime <= 0.f) {
            //Firetime reduces everytime update is called, once  it is 0 the player can fire another bullet
			auto playerPhysics = _parent->get_components<PhysicsComponent>()[0];
			//playerPhysics->setFriction(0.1f);
			playerPhysics->setMass(50.0f);
			playerPhysics->setTimer();
			Vector2f impulse = sf::rotate(Vector2f(0, 5.f), playerSprite->getSprite().getRotation());
			impulse = Vector2f(-impulse.x, impulse.y);
			playerPhysics->impulse(impulse);

            auto playerSprite = _parent->get_components<SpriteComponent>()[0];
            float rotation = playerSprite->getSprite().getRotation(); //Gets current rotation of player sprite
            auto bullet = _parent->scene->makeEntity();
            bullet->setPosition(_parent->getPosition());    //Sets bullet position to player position
            auto b = bullet->addComponent<BaseBulletComponent>(); //Adds bullet component which determines bullet pickup
            auto s = bullet->addComponent<SpriteComponent>(); //Adds sprite component

            bulletSprite.setTexture(sprite);   
            bulletSprite.setScale({ 0.1f, 0.1f });  //Sets scale of bullet CHANGE TO VARIABLE FOR LATER USE
            bulletSprite.setOrigin({ 200, 200 });   //sets center of bullet
            bulletSprite.setPosition(_parent->getPosition());   //sets position of sprite to be same as object
            s->setSprite<Sprite>(bulletSprite);
            float inverse = fmod((rotation + 180.f), 360);  //Sets rotation of bullet to be inverse of ship rotation, using fancy maths.
            bullet->setRotation(inverse);

            float frate = b->getFRate(); //Firerate set by bullet component, allows reduction in firetime when necessary
            _firetime = frate;
        }
        //move(dt, (300.f)); 
    }
}

void PlayerFireComponent::render() {} //empty required method
