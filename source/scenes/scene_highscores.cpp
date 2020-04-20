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
		std::vector<std::string> names;
		std::vector<int> scores;
		int score;
		string name;
		
		while (inFile >> score >> name) {
			scores.push_back(score);
			names.push_back(name);
		}
		inFile.close();

		//Simple bubble sort (because you need to sort the names based on the scores being sorted)
		int tempi;
		string temp;
		for (int i = 0; i < scores.size(); i++) {
			for (int j = i + 1; j < scores.size(); j++)
			{
				if (scores[j] > scores[i]) {
					tempi = scores[i];
					scores[i] = scores[j];
					scores[j] = tempi;

					temp = names[i];
					names[i] = names[j];
					names[j] = temp;

				}
			}
		}


	cout << "Menu Load \n";
	{
		auto txt = makeEntity();
		ostringstream output;
\
		for (size_t i = 0; i < names.size(); i++)
		{
		output << setw(25) << left << scores[i] << names[i] << endl;
		//cout << output.str() << endl;
		}

		auto t = txt->addComponent<TextComponent>(output.str());
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
