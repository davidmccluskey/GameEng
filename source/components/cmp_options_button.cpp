#include "cmp_options_button.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "cmp_text.h"
#include "../game.h"
#include <fstream>
#include "../options.h"
using namespace std;
using namespace sf;
// Constructor

OptionsItemComponent::OptionsItemComponent(Entity* p, std::string txt, Vector2f size) : Component(p)
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

void OptionsItemComponent::update(double dt) {
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

void OptionsItemComponent::setSize(float textSize, float windowSize)
{
	auto text = _parent->get_components<TextComponent>()[0];
	text->SetSize(textSize);
	auto sprite = _parent->get_components<ShapeComponent>()[0];
	sprite->getShape().setScale({ windowSize, windowSize });

}

void OptionsItemComponent::setPosition(Vector2f position)
{
	auto text = _parent->get_components<TextComponent>()[0];
	text->SetPosition({position.x + 20, position.y - 5});
	auto sprite = _parent->get_components<ShapeComponent>()[0];
	_parent->setPosition(position);
}

void OptionsItemComponent::render()
{
}

void OptionsItemComponent::setTextColour(sf::Color color)
{
	auto text = _parent->get_components<TextComponent>()[0];
	text->SetColour(color);
}

void OptionsItemComponent::setBorderColour(sf::Color color)
{
	auto shape = _parent->get_components<ShapeComponent>()[0];
	shape->getShape().setOutlineColor(color);
}

void OptionsItemComponent::resolveClick() {
	auto tagSet = _parent->getTags();
	string parentTag = tagSet.begin()->c_str();
	clickCooldown = 0.2;

	if (parentTag == "volumeUp") {
		int volume = Options::instance()->volume;
		if (volume < 100) {
			volume = volume + 25;
		}
		music.setVolume(volume);
		Options::instance()->volume = volume;
		//cout << "volume up" << endl;
		//cout << Options::instance()->volume << endl;
	}else if(parentTag == "volumeDown") {
		int volume = Options::instance()->volume;
		volume = volume - 25;
		music.setVolume(volume);
		Options::instance()->volume = volume;
		//cout << "volume down" << endl;
		//cout << Options::instance()->volume << endl;
	}
	else if (parentTag == "effectsOn") {
		Options::instance()->effectsOn = true;
		cout << "effects " << Options::instance()->effectsOn << endl;
	}
	else if (parentTag == "effectsOff") {
		Options::instance()->effectsOn = false;
		cout << "effects " << Options::instance()->effectsOn << endl;
	}
	else if (parentTag == "musicOn") {
		Options::instance()->musicOn = true;
		cout << "music " << Options::instance()->musicOn << endl;
		music.setVolume(Options::instance()->volume);
	}
	else if (parentTag == "musicOff") {
		Options::instance()->musicOn = false;
		cout << "music " << Options::instance()->musicOn << endl;
		music.setVolume(0);
	}
	else if (parentTag == "resOne") {
		Options::instance()->width = 1920;
		Options::instance()->height = 1080;
		cout << "resolution " << Options::instance()->width << Options::instance()->height << endl;
	}
	else if (parentTag == "resTwo") {
		//Options::instance()->resolution = "1600x900";
		Options::instance()->width = 1600;
		Options::instance()->height = 900;
		cout << "resolution " << Options::instance()->width << Options::instance()->height << endl;
		//cout << "resolution " << Options::instance()->resolution << endl;
	}
	else if (parentTag == "resThree") {
		//Options::instance()->resolution = "1280x720";
		Options::instance()->width = 1280;
		Options::instance()->height = 720;
		cout << "resolution " << Options::instance()->width << Options::instance()->height << endl;
		//cout << "resolution " << Options::instance()->resolution << endl;
	}
	else if (parentTag == "resFour") {
		//Options::instance()->resolution = "2560x1440";
		Options::instance()->width = 2560;
		Options::instance()->height = 1440;
		cout << "resolution " << Options::instance()->width << Options::instance()->height << endl;
		//cout << "resolution " << Options::instance()->resolution << endl;
	}
	else if (parentTag == "fullscreen") {
		Options::instance()->windowMode = 1;
		cout << "window mode " << Options::instance()->windowMode << endl;
	}
	else if (parentTag == "windowed") {
		Options::instance()->windowMode = 0;
		cout << "window mode " << Options::instance()->windowMode << endl;
	}
}