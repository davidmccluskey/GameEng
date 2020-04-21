#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_menu.h"
#include "../components/cmp_options_button.h"
#include "scene_controls.h"
#include "../options.h"
#include "../components/cmp_controls_button.h"
using namespace std;
using namespace sf;

void ControlsScreen::Load() {
	{
		cout << music.getVolume() << endl;
		auto back = makeEntity();
		back->addTag("ctrlBack");

		back->setPosition({ gameWidth * 0.15, gameHeight * 0.9 });

		auto s = back->addComponent<MenuItemComponent>("Back");
		s->setSize(30, 0.7);
	}

	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Controls");
		t->SetSize(50);
		t->SetPosition({ gameWidth * 0.05, 20 });
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Move Left");
		t->SetSize(30);
		t->SetPosition({ gameWidth * 0.05, 100 });

		auto moveLeft = makeEntity();
		string str = to_string(Options::instance()->moveLeft);
		auto crc = moveLeft->addComponent<ControlRemapComponent>(str, Vector2f(100, 50));
		crc->setPosition({ gameWidth * 0.4, 100 });
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Move Right");
		t->SetSize(30);
		t->SetPosition({ gameWidth * 0.05, 200 });

		auto moveLeft = makeEntity();
		string str = to_string(Options::instance()->moveRight);
		auto crc = moveLeft->addComponent<ControlRemapComponent>(str, Vector2f(100, 50));
		crc->setPosition({ gameWidth * 0.4, 200 });
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Shoot");
		t->SetSize(30);
		t->SetPosition({ gameWidth * 0.05, 300 });

		auto moveLeft = makeEntity();
		string str = to_string(Options::instance()->shootKey);
		auto crc = moveLeft->addComponent<ControlRemapComponent>(str, Vector2f(100, 50));
		crc->setPosition({ gameWidth * 0.4, 300 });
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Pause");
		t->SetSize(30);
		t->SetPosition({ gameWidth * 0.05, 400 });

		auto moveLeft = makeEntity();
		//string str = to_string();
		char character = char(Options::instance()->pauseKey + 65);
		string str = to_string(character);
		auto crc = moveLeft->addComponent<ControlRemapComponent>(str, Vector2f(100, 50));
		crc->setPosition({ gameWidth * 0.4, 400 });
	}
	setLoaded(true);
}

void ControlsScreen::Update(const double& dt) {
	clickCooldown -= dt;
	
	sf::Event event;
	RenderWindow& window = Engine::GetWindow();
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Engine::ChangeScene(&menu);
	}

	Scene::Update(dt);
}

void ControlsScreen::UnLoad() {
	cout << "Scene 1 Unload" << endl;
	//player.reset();
	Scene::UnLoad();
}
