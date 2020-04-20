#include "scene_highscores.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_menu.h"
#include <fstream>

using namespace std;
using namespace sf;

void HighScoreScene::Load() {
	_paused = false;
	View view = Engine::GetWindow().getView();
	view.setCenter({ gameWidth / 2, gameHeight / 2 });
	Engine::GetWindow().setView(view);
	auto back = makeEntity();
	back->addTag("back");

	back->setPosition({ gameWidth * 0.15, gameHeight * 0.9 });
	auto s = back->addComponent<MenuItemComponent>("Back");

	ifstream inFile;
	inFile.open("scores.txt");
	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}
	//inFile.getline()
	
	inFile.close();
	cout << "Menu Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Dummy high score screen, press space to return");
	}
	setLoaded(true);
}

void HighScoreScene::Update(const double& dt) {
	clickCooldown -= dt;
	// cout << "Menu Update "<<dt<<"\n";
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
