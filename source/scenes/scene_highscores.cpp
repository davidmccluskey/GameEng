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
	auto back = makeEntity();
	back->addTag("back");


	back->setPosition(Vector2f(windowWidth * 0.15, windowHeight * 0.9));
	auto s = back->addComponent<MenuItemComponent>("Back");
	s->setSize(30, 0.7);

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
		ostringstream namesoutput;
		ostringstream scoresoutput;
		ostringstream nums;
		int numTimes = 0;
		if (names.size() > 20) {
			numTimes = 20;
		}
		else {
			numTimes = names.size();
		}
		for (size_t i = 0; i < numTimes; i++)
		{
			scoresoutput << scores[i] << endl;
			namesoutput << names[i] << endl;
			nums << i + 1 << "." << endl;
		}
		auto numbers = txt->addComponent<TextComponent>(nums.str());
		numbers->SetPosition(Vector2f(windowWidth * 0.1, windowHeight * 0.1));

		auto tScr = txt->addComponent<TextComponent>(scoresoutput.str());
		tScr->SetPosition(Vector2f(windowWidth * 0.2, windowHeight * 0.1));

		auto tName = txt->addComponent<TextComponent>(namesoutput.str());
		tName->SetPosition(Vector2f(windowWidth * 0.4, windowHeight * 0.1));

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
