#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML\Window\Mouse.hpp>
#include <system_renderer.h>
#include "../components/cmp_sprite.h"
#include "../components/cmp_menu.h"
#include <SFML\Audio\Music.hpp>
#include "../options.h"

using namespace std;
using namespace sf;

Texture background;
Sprite spriteBackground;



void MenuScene::Load() {
	View view = Engine::GetWindow().getDefaultView();
	//View view;
	//view.setSize(gameWidth / 3, gameHeight / 3);
	//if (_paused == true) {
	//	view.zoom(1);
	//}
	_paused = false;

	float scaleWidth = windowWidth/1600;
	float scaleHeight = windowHeight/900;
	//view.setCenter({windowWidth / 2, windowHeight / 2 });
	Engine::GetWindow().setView(view);

	if (Options::instance()->musicOn == true) {
		if (music.getStatus() != 2)
		{
			if (!music.openFromFile("res/soundFX/menu_music.WAV")) {
				cout << "error loading music" << endl;
			}
			else {
				music.setVolume(Options::instance()->volume);
				music.play();

			}
		}
	}
	cout << "Menu Load \n";
	if (background.loadFromFile("res/background.jpeg")) {
		spriteBackground.setTexture(background);
		spriteBackground.setPosition(0, 0);
		spriteBackground.setScale({ scaleWidth, scaleHeight });
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
		//auto txt = makeEntity();
		//auto t = txt->addComponent<TextComponent>("Gunthrusters");
		//t->SetPosition({ 70, gameHeight * 0.10 });
		//t->SetSize(60);
		//t->SetColour(sf::Color::White);

	}
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
	clickCooldown -= dt;
	sf::Event event;
	RenderWindow& window = Engine::GetWindow();
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}
	}
	// cout << "Menu Update "<<dt<<"\n";
	if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
		Engine::ChangeScene(&scene_main);
		music.stop();
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

void MenuScene::UnLoad() {
	cout << "Scene 1 Unload" << endl;
	//player.reset();
	Scene::UnLoad();
}
