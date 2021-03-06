#include "cmp_menu.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "cmp_text.h"
#include <engine.cpp>
#include "../game.h"
#include <fstream>
#include "../options.h"
#include "../texture.h"

using namespace std;
using namespace sf;
// Constructor
Sprite spriteMenu;

MenuItemComponent::MenuItemComponent(Entity* p, std::string Text) : Component(p)
{
	auto s = _parent->addComponent<SpriteComponent>();
	
		spriteMenu.setTexture(Textures::instance()->getMenuItem());
		s->setSprite<Sprite>(spriteMenu);
		s->getSprite().setOrigin(200, 25);

		auto txt = _parent->addComponent<TextComponent>(Text);
		sf::Text txtRef = txt->getText();
		txt->SetOrigin({ (txtRef.getLocalBounds().getSize().x / 2), (txtRef.getLocalBounds().getSize().y / 2) });
		txt->SetPosition({ _parent->getPosition().x,_parent->getPosition().y });
		txt->SetSize(40);
	

}

void MenuItemComponent::update(double dt) {
	auto mouse_pos = Mouse::getPosition(Engine::GetWindow());
	float parentX = _parent->getPosition().x;
	float parentY = _parent->getPosition().y;

	if (clickCooldown < 0) {
		auto tagSet = _parent->getTags();
		string parentTag = tagSet.begin()->c_str();
		if ((parentTag == "resume" || parentTag == "home" || parentTag == "restart") && _paused == true) {
			auto sprite = _parent->get_components<SpriteComponent>()[0];
			FloatRect rect = sprite->getSprite().getLocalBounds();
			if ((mouse_pos.x - windowWidth) > (sprite->getSprite().getPosition().x - (rect.width / 2) - 50) && (mouse_pos.x - windowWidth) < (sprite->getSprite().getPosition().x + (rect.width / 2)) && (mouse_pos.y - windowHeight) > (sprite->getSprite().getPosition().y - 50) && (mouse_pos.y - windowHeight) < (sprite->getSprite().getPosition().y + 50)) {
				auto text = _parent->get_components<TextComponent>()[0];
				text->SetColour(sf::Color::White);
				sprite->getSprite().setColor(sf::Color::Red);

				if (sf::Mouse::isButtonPressed(Mouse::Left)) {
					resolveClick();
				}
			}
			else {
				auto text = _parent->get_components<TextComponent>()[0];
				text->SetColour(sf::Color::White);
				auto sprite = _parent->get_components<SpriteComponent>()[0];
				sprite->getSprite().setColor(sf::Color::White);
			}
		}
		else {
			if ((mouse_pos.x > parentX - 150) && (mouse_pos.x < parentX + 250) && (mouse_pos.y > parentY - 50) && (mouse_pos.y < parentY + 50)) {
				auto text = _parent->get_components<TextComponent>()[0];
				auto sprite = _parent->get_components<SpriteComponent>()[0];
				text->SetColour(sf::Color::White);
				sprite->getSprite().setColor(sf::Color::Red);

				if (sf::Mouse::isButtonPressed(Mouse::Left)) {
					resolveClick();
				}
			}
			else {
				auto text = _parent->get_components<TextComponent>()[0];
				text->SetColour(sf::Color::White);
				auto sprite = _parent->get_components<SpriteComponent>()[0];
				sprite->getSprite().setColor(sf::Color::White);
			}
		}
	}

}

void MenuItemComponent::resolveClick() {
	auto tagSet = _parent->getTags();
	string parentTag = tagSet.begin()->c_str();
	clickCooldown = 0.2;
	//cout << parentTag << "Clicked" << endl;

	if (parentTag == "start") {
		music.stop();
		Engine::ChangeScene(&scene_main);
		return;
	}
	else if (parentTag == "exit") {
		Engine::GetWindow().close();
	}
	else if (parentTag == "options" || parentTag == "ctrlBack") {
		Engine::ChangeScene(&scene_settings);
		return;
	}
	else if (parentTag == "highscore") {
		Engine::ChangeScene(&scene_highscores);
		return;
	}
	else if (parentTag == "back") {
		Engine::ChangeScene(&menu);
		return;
	}
	else if (parentTag == "save") {
		Options::instance()->save();
		Engine::ChangeScene(&menu);
		return;
	}
	else if (parentTag == "resume") {
		_paused = false;
		return;
	}
	else if (parentTag == "restart") {
		Engine::ChangeScene(&scene_main);
		return;
	}
	else if (parentTag == "home") {
		Engine::ChangeScene(&menu);
		return;
		
	}
	else if (parentTag == "controls") {
		Engine::ChangeScene(&scene_controls);
		return;
	}
	else if (parentTag == "enter score") {
		if (name != "") {
			cout << score.getScore() << name << endl;
			string str = to_string(score.getScore());
			str.resize(str.size() - 7);

			std::ofstream outfile;
			string output = str + " " + name + "\n";
			outfile.open("scores.txt", std::ios_base::app); // append instead of overwrite
			outfile << output;
			Engine::ChangeScene(&scene_highscores);
			outfile.close();
		}
		else { cout << "please enter a name" << endl; }
		return;
	}
	else if (parentTag == "credits") {
		Engine::ChangeScene(&scene_credits);
		return;
	}

}

void MenuItemComponent::setSize(float textSize, float windowSize)
{
	auto text = _parent->get_components<TextComponent>()[0];
	text->SetSize(textSize);
	auto sprite = _parent->get_components<SpriteComponent>()[0];
	sprite->getSprite().setScale({ windowSize, windowSize });

}
void MenuItemComponent::render()
{
}
