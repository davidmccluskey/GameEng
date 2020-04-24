#include "scene_credits.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_menu.h"
#include <fstream>

using namespace std;
using namespace sf;

void CreditsScene::Load() {
	_paused = false;


	cout << "Menu Load \n";
	{
		auto back = makeEntity();
		back->addTag("back");
		back->setPosition(Vector2f(windowWidth * 0.15, windowHeight * 0.9));
		auto s = back->addComponent<MenuItemComponent>("Back");
		s->setSize(30, 0.7);
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Credits");
		t->SetSize(50);
		t->SetPosition({ gameWidth * 0.05, 20 });
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Game programming and game design\n - Bradley Rayner");
		t->SetSize(40);
		t->SetPosition({ gameWidth * 0.05, 100 }); 
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Engine programming and game design\n - David McCluskey");
		t->SetSize(40);
		t->SetPosition({ gameWidth * 0.05, 225 });
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Art and Illustration\n - Mary-Ann Henry (Instagram @penciltower)");
		t->SetSize(40);
		t->SetPosition({ gameWidth * 0.05, 350 });
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Music from Youtube Royalty free library.");
		t->SetSize(30);
		t->SetPosition({ gameWidth * 0.05, 475 });
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Sound effects from 'freesound.org'");
		t->SetSize(30);
		t->SetPosition({ gameWidth * 0.05, 525 });
	}
	setLoaded(true);
}

void CreditsScene::Update(const double& dt) {
	clickCooldown -= dt;
	// cout << "Menu Update "<<dt<<"\n";
	sf::Event event;
	RenderWindow& window = Engine::GetWindow();
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}
	}

	Scene::Update(dt);
}
