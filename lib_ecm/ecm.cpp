#include "ecm.h"

// Entity class 
//Constructor
Entity::Entity() {}
Entity::~Entity(){}
// Update method
void Entity::update(double dt) {
	for (size_t i = 0; i < _components.size(); i++)
	{
		_components[i]->update(dt);
	}
}

// Render methods
void Entity::render() {
	if (!_visible)
	{
		return;
	}
	for (auto& c : _components)
	{
		c->render();
	}
}

// Position methods
const sf::Vector2f& Entity::getPosition() const { return _position; }
void Entity::setPosition(const sf::Vector2f& pos) { _position = pos; }

// Deletion methods
bool Entity::is_fordeletion() const { return _fordeletion; }
void Entity::setForDelete() { _fordeletion = true; }

// Rotation methods
float Entity::getRotation() const {

	return _rotation;
}
void Entity::setRotation(float rot) { _rotation = rot; }

// Alive methods
bool Entity::isAlive() const { return _alive; }
void Entity::setAlive(bool alv) { _alive = alv; }

// Visible methods
bool Entity::isVisible() const { return _visible; }
void Entity::setVisible(bool vis) { _visible = vis; }

// Component class
// Constructor
Component::Component(Entity* const p) : _parent(p), _fordeletion(false) {}

// Destructor
Component::~Component() {}

// Deletion method
bool Component::is_fordeletion() const { return _fordeletion; }

void EntityManager::update(double dt)
{
	for (size_t i = 0; i < list.size(); i++)
	{

			list[i]->update(dt);
	}
}

void EntityManager::render()
{
	for (auto& e : list)
	{
		e->render();
	}
}