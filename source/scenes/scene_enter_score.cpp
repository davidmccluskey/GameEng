#include "scene_settings.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_menu.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> nameText;
static shared_ptr<TextComponent> nameTextComponent;

void EnterScoreScreen::Load() {
	View view = Engine::GetWindow().getView();
	view.setCenter({ gameWidth / 2, gameHeight / 2 });
	Engine::GetWindow().setView(view);
	auto back = makeEntity();
	back->addTag("enter score");
	back->setPosition({ gameWidth * 0.5, gameHeight * 0.8 });

	auto s = back->addComponent<MenuItemComponent>("Enter");

	cout << "Menu Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Please enter your name");
		t->SetPosition({ gameWidth / 2 - 200, 200 });
	}
	{
		auto txt = makeEntity();
		string str = to_string(score.getScore());
		str.resize(str.size() - 7);
		auto t = txt->addComponent<TextComponent>("Final Score: " + str);
		t->SetPosition({ gameWidth / 2 - 100, 100 });
	}
	nameText = makeEntity();
	nameTextComponent = nameText->addComponent<TextComponent>(
		"");
	nameTextComponent->SetPosition({ gameWidth / 2 - 200, 300 });
	nameTextComponent->SetSize(70);
	setLoaded(true);
}

void EnterScoreScreen::Update(const double& dt) {
	_keyboardCooldown -= dt;
	clickCooldown -= dt;
	RenderWindow& window = Engine::GetWindow();
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode == '\b') {
				if (name.size() != 0) {
					name.resize(name.size() - 1);
					nameTextComponent->SetText(name);
				}
			}else if (event.text.unicode == 13) {
				cout << "enter pressed" << endl;
			}
			else if (event.text.unicode == 9) {
				cout << "tab pressed" << endl;
			}
			else if (event.text.unicode == 32) {
				cout << "space pressed" << endl;
			}
			else {
				//std::cout << "ASCII character typed: " << event.text.unicode << std::endl;
				if (name.size() != 10) {
					name = name + event.text.unicode;
					nameTextComponent->SetText(name);
				}
				else{
					cout << "too long" << endl;
				}

			}

		}
	}



	Scene::Update(dt);
}
