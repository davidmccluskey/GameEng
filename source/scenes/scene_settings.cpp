#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../components/cmp_menu.h"
#include "../components/cmp_options_button.h"
#include "../options.h"
using namespace std;
using namespace sf;

static shared_ptr<TextComponent> volumeTextComponent;
static shared_ptr<OptionsItemComponent> musicOnComponent;
static shared_ptr<OptionsItemComponent> musicOffComponent;
static shared_ptr<OptionsItemComponent> effectsOnComponent;
static shared_ptr<OptionsItemComponent> effectsOffComponent;
static shared_ptr<OptionsItemComponent> resOneComponent;
static shared_ptr<OptionsItemComponent> resTwoComponent;
static shared_ptr<OptionsItemComponent> resThreeComponent;
static shared_ptr<OptionsItemComponent> resFourComponent;
static shared_ptr<OptionsItemComponent> fullscreenComponent;
static shared_ptr<OptionsItemComponent> windowedComponent;


void SettingsScreen::Load() {
	{
		cout << music.getVolume() << endl;
		auto back = makeEntity();
		back->addTag("save");

		back->setPosition({ gameWidth * 0.15, gameHeight * 0.9 });

		auto s = back->addComponent<MenuItemComponent>("Back");
		s->setSize(30, 0.7);
	}
	{
		auto controls = makeEntity();
		controls->addTag("controls");

		controls->setPosition({ gameWidth * 0.8, gameHeight * 0.9 });

		auto sa = controls->addComponent<MenuItemComponent>("Controls");
		sa->setSize(30, 0.7);
	}

	cout << "Menu Load \n";
	{

		{
			auto txt = makeEntity();
			auto t = txt->addComponent<TextComponent>("Music");
			t->SetSize(40);
			t->SetPosition({ gameWidth * 0.05, 100 });
		}

		{
			auto txt = makeEntity();
			auto t = txt->addComponent<TextComponent>("Effects");
			t->SetSize(40);
			t->SetPosition({ gameWidth * 0.05, 200 });
		}
		{
			auto txt = makeEntity();
			auto t = txt->addComponent<TextComponent>("Volume");
			t->SetSize(40);
			t->SetPosition({ gameWidth * 0.05, 300 });
		}
		{
			auto offBtn = makeEntity();
			musicOffComponent = offBtn->addComponent<OptionsItemComponent>("Off", Vector2f(100, 50));
			musicOffComponent->setPosition({ gameWidth * 0.4, 100 });
			offBtn->addTag("musicOff");

			auto onBtn = makeEntity();
			musicOnComponent = onBtn->addComponent<OptionsItemComponent>("On", Vector2f(100, 50));
			musicOnComponent->setPosition({ gameWidth * 0.3, 100 });
			onBtn->addTag("musicOn");
		}
		{
			auto offBtn = makeEntity();
			effectsOffComponent = offBtn->addComponent<OptionsItemComponent>("Off", Vector2f(100, 50));
			effectsOffComponent->setPosition({ gameWidth * 0.4, 200 });
			offBtn->addTag("effectsOff");

			auto onBtn = makeEntity();
			effectsOnComponent = onBtn->addComponent<OptionsItemComponent>("On", Vector2f(100, 50));
			effectsOnComponent->setPosition({ gameWidth * 0.3, 200 });
			onBtn->addTag("effectsOn");
		}
		{
			auto onBtn = makeEntity();
			auto t = onBtn->addComponent<OptionsItemComponent>("+", Vector2f(100, 50));
			t->setPosition({ gameWidth * 0.4, 300 });
			onBtn->addTag("volumeUp");

			auto volumeText = makeEntity();

			volumeTextComponent = volumeText->addComponent<TextComponent>("");
			volumeTextComponent->SetSize(40);
			volumeTextComponent->SetPosition({ gameWidth * 0.2, 300 });

			auto offBtn = makeEntity();
			auto btn = offBtn->addComponent<OptionsItemComponent>("-", Vector2f(100, 50));
			btn->setPosition({ gameWidth * 0.3, 300 });
			offBtn->addTag("volumeDown");
		}

		{
			{
				{
					auto onBtn = makeEntity();
					resOneComponent = onBtn->addComponent<OptionsItemComponent>("1920x1080", Vector2f(250, 50));
					resOneComponent->setPosition({ gameWidth * 0.55, 100 });
					onBtn->addTag("resOne");
				}
				{
					auto onBtn = makeEntity();
					resTwoComponent = onBtn->addComponent<OptionsItemComponent>("1600x900", Vector2f(250, 50));
					resTwoComponent->setPosition({ gameWidth * 0.55, 200 });
					onBtn->addTag("resTwo");
				} 
				{
					auto onBtn = makeEntity();
					resThreeComponent = onBtn->addComponent<OptionsItemComponent>("1280x720", Vector2f(250, 50));
					resThreeComponent->setPosition({ gameWidth * 0.8, 100 });
					onBtn->addTag("resThree");

				}
				{
					auto onBtn = makeEntity();
					resFourComponent = onBtn->addComponent<OptionsItemComponent>("2560x1440", Vector2f(250, 50));
					resFourComponent->setPosition({ gameWidth * 0.8, 200 });
					onBtn->addTag("resFour");

				}
				{
					auto onBtn = makeEntity();
					fullscreenComponent = onBtn->addComponent<OptionsItemComponent>("Fullscreen", Vector2f(250, 50));
					fullscreenComponent->setPosition({ gameWidth * 0.55, 300 });
					onBtn->addTag("fullscreen");
				}
				{
					auto onBtn = makeEntity();
					windowedComponent = onBtn->addComponent<OptionsItemComponent>("Windowed", Vector2f(250, 50));
					windowedComponent->setPosition({ gameWidth * 0.8, 300 });
					onBtn->addTag("windowed");

				}
			}
		}
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Resolution");
		t->SetSize(50);
		t->SetPosition({ gameWidth * 0.55, 20 });
		//t->SetPosition({ 100, 100 });
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Sound");
		t->SetSize(50);
		t->SetPosition({ gameWidth * 0.05, 20 });
	}
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Note, any resolution changes\nrequire restart.");
		t->SetSize(30);
		t->SetPosition({ gameWidth * 0.55, gameHeight * 0.55 });
	}
	setLoaded(true);
}

void SettingsScreen::Update(const double& dt) {
	clickCooldown -= dt;
	if (Options::instance()->effectsOn == true) {
		effectsOffComponent->setTextColour(Color(105,105,105));
		effectsOnComponent->setTextColour(Color::White);

		effectsOffComponent->setBorderColour(Color(105, 105, 105));
		effectsOnComponent->setBorderColour(Color::White);

	}else if (Options::instance()->effectsOn == false) {
		effectsOnComponent->setTextColour(Color(105, 105, 105));
		effectsOffComponent->setTextColour(Color::White);

		effectsOnComponent->setBorderColour(Color(105, 105, 105));
		effectsOffComponent->setBorderColour(Color::White);
	}
	if (Options::instance()->musicOn == true) {
		musicOffComponent->setTextColour(Color(105, 105, 105));
		musicOnComponent->setTextColour(Color::White);

		musicOffComponent->setBorderColour(Color(105, 105, 105));
		musicOnComponent->setBorderColour(Color::White);

	}
	else if (Options::instance()->musicOn == false) {
		musicOnComponent->setTextColour(Color(105, 105, 105));
		musicOffComponent->setTextColour(Color::White);

		musicOnComponent->setBorderColour(Color(105, 105, 105));
		musicOffComponent->setBorderColour(Color::White);
	}
	if (Options::instance()->windowMode == true) {
		windowedComponent->setTextColour(Color(105, 105, 105));
		fullscreenComponent->setTextColour(Color::White);

		windowedComponent->setBorderColour(Color(105, 105, 105));
		fullscreenComponent->setBorderColour(Color::White);

	}
	else if (Options::instance()->windowMode == false) {
		fullscreenComponent->setTextColour(Color(105, 105, 105));
		windowedComponent->setTextColour(Color::White);

		fullscreenComponent->setBorderColour(Color(105, 105, 105));
		windowedComponent->setBorderColour(Color::White);
	}
	if (Options::instance()->width == 1920) {
		resOneComponent->setTextColour(Color::White);
		resOneComponent->setBorderColour(Color::White);

		resTwoComponent->setTextColour(Color(105, 105, 105));
		resTwoComponent->setBorderColour(Color(105, 105, 105));
		resThreeComponent->setTextColour(Color(105, 105, 105));
		resThreeComponent->setBorderColour(Color(105, 105, 105));
		resFourComponent->setBorderColour(Color(105, 105, 105));
		resFourComponent->setTextColour(Color(105, 105, 105));
	}
	else if (Options::instance()->width == 1600) {
		resTwoComponent->setTextColour(Color::White);
		resTwoComponent->setBorderColour(Color::White);

		resOneComponent->setTextColour(Color(105, 105, 105));
		resOneComponent->setBorderColour(Color(105, 105, 105));
		resThreeComponent->setTextColour(Color(105, 105, 105));
		resThreeComponent->setBorderColour(Color(105, 105, 105));
		resFourComponent->setBorderColour(Color(105, 105, 105));
		resFourComponent->setTextColour(Color(105, 105, 105));
	}
	else if (Options::instance()->width == 1280) {
		resThreeComponent->setTextColour(Color::White);
		resThreeComponent->setBorderColour(Color::White);

		resTwoComponent->setTextColour(Color(105, 105, 105));
		resTwoComponent->setBorderColour(Color(105, 105, 105));
		resOneComponent->setTextColour(Color(105, 105, 105));
		resOneComponent->setBorderColour(Color(105, 105, 105));
		resFourComponent->setBorderColour(Color(105, 105, 105));
		resFourComponent->setTextColour(Color(105, 105, 105));
	}
	else if (Options::instance()->width == 2560) {
		resFourComponent->setTextColour(Color::White);
		resFourComponent->setBorderColour(Color::White);

		resTwoComponent->setTextColour(Color(105, 105, 105));
		resTwoComponent->setBorderColour(Color(105, 105, 105));
		resThreeComponent->setTextColour(Color(105, 105, 105));
		resThreeComponent->setBorderColour(Color(105, 105, 105));
		resOneComponent->setBorderColour(Color(105, 105, 105));
		resOneComponent->setTextColour(Color(105, 105, 105));
	}
	string volumeStr = to_string(Options::instance()->volume);
	volumeTextComponent->SetText(volumeStr);
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

void SettingsScreen::UnLoad() {
	cout << "Scene 1 Unload" << endl;
	Scene::UnLoad();
}
