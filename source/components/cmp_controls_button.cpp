#include "cmp_controls_button.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "cmp_text.h"
#include "../game.h"
#include <fstream>
#include "../options.h"
using namespace std;
using namespace sf;
// Constructor

ControlRemapComponent::ControlRemapComponent(Entity* p, std::string txt, Vector2f size) : Component(p)
{
	auto s = _parent->addComponent<ShapeComponent>();
	s->setShape<sf::RectangleShape>(size);
	s->getShape().setFillColor(Color::Transparent);
	s->getShape().setOutlineThickness(2);
	s->getShape().setOutlineColor(Color::White);

	//s->getShape().setOrigin(50, 25);
	// change the size to 100x100
	//rectangle.setSize(sf::Vector2f(100, 100));

	auto text = _parent->addComponent<TextComponent>(txt);
	text->SetSize(40);
}

void ControlRemapComponent::update(double dt) {
	auto mouse_pos = Mouse::getPosition(Engine::GetWindow());
	float parentX = _parent->getPosition().x;
	float parentY = _parent->getPosition().y;
	if (clickCooldown < 0) {
		auto shape = _parent->get_components<ShapeComponent>()[0];
		FloatRect shapeSize = shape->getShape().getGlobalBounds();
		if ((mouse_pos.x > parentX) && (mouse_pos.x < parentX + (shapeSize.width)) && (mouse_pos.y > parentY) && (mouse_pos.y < parentY + (shapeSize.height))) {
			if (sf::Mouse::isButtonPressed(Mouse::Left)) {
				resolveClick();
			}
		}
	}
}

void ControlRemapComponent::setSize(float textSize, float windowSize)
{
	auto text = _parent->get_components<TextComponent>()[0];
	text->SetSize(textSize);
	auto sprite = _parent->get_components<ShapeComponent>()[0];
	sprite->getShape().setScale({ windowSize, windowSize });

}

void ControlRemapComponent::setPosition(Vector2f position)
{
	auto text = _parent->get_components<TextComponent>()[0];
	text->SetPosition({position.x + 20, position.y - 5});
	auto sprite = _parent->get_components<ShapeComponent>()[0];
	_parent->setPosition(position);
}

void ControlRemapComponent::render()
{
}

void ControlRemapComponent::setTextColour(sf::Color color)
{
	auto text = _parent->get_components<TextComponent>()[0];
	text->SetColour(color);
}

void ControlRemapComponent::setBorderColour(sf::Color color)
{
	auto shape = _parent->get_components<ShapeComponent>()[0];
	shape->getShape().setOutlineColor(color);
}


void ControlRemapComponent::setText(string inputText)
{
	auto text = _parent->get_components<TextComponent>()[0];
	text->SetText(inputText);
}

void ControlRemapComponent::resolveClick() {
	
}