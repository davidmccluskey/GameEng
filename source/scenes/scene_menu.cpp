#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML\Window\Mouse.hpp>
#include <system_renderer.h>
#include "../components/cmp_sprite.h"
#include "../components/cmp_menu.h"

using namespace std;
using namespace sf;

Texture background;
Sprite spriteBackground;

void MenuScene::Load() {
	cout << "Menu Load \n";
	if (background.loadFromFile("res/background.jpeg")) {
		spriteBackground.setTexture(background);
		spriteBackground.setPosition(0, 0);
	}
	{

		auto start = makeEntity();
		start->addTag("start");

		auto highscore = makeEntity();
		highscore->addTag("highscore");

		auto options = makeEntity();
		options->addTag("options");

		auto exit = makeEntity();
		exit->addTag("exit");

		start->setPosition({ 250, gameHeight * 0.40 });
		highscore->setPosition({ 250, gameHeight * 0.55 });
		options->setPosition({ 250, gameHeight * 0.70 });
		exit->setPosition({ 250, gameHeight * 0.85 });

		auto s = start->addComponent<MenuItemComponent>("Start");
		auto h = highscore->addComponent<MenuItemComponent>("High Scores");
		auto o = options->addComponent<MenuItemComponent>("Options");
		auto e = exit->addComponent<MenuItemComponent>("Exit");



	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Gunthrusters");
		t->SetPosition({ 70, gameHeight * 0.10 });
		t->SetSize(60);
		t->SetColour(sf::Color::Red);

	}
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
	// cout << "Menu Update "<<dt<<"\n";
	static bool mouse_down = false;
	auto mouse_pos = Mouse::getPosition(Engine::GetWindow());

	if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
		Engine::ChangeScene(&scene_main);
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
		Engine::ChangeScene(&scene_highscores);
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::Num3)) {
		Engine::ChangeScene(&scene_settings);
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::Num4)) {
		exit(EXIT_FAILURE);
	}

	Scene::Update(dt);
}

void MenuScene::Render()
{
	Renderer::queue(&spriteBackground);
	Scene::Render();
}

void MenuScene::Render()
{
    Renderer::queue(&spriteBackground);
    Scene::Render();
}
