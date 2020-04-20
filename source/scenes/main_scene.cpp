#include "main_scene.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include "../components/cmp_text.h"
#include "../components/cmp_player_movement.h"
#include "../components/cmp_player_fire.h"
#include "system_resources.h"
#include "../components/cmp_physics.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "system_renderer.h"
#include <random>
#include <chrono>
#include "../components/cmp_ai_steering.h"
#include<string>
#include "system_physics.h"
#include "../contactListener.cpp"
#include "../components/cmp_base_enemy.h"
#include "../components/cmp_state_machine.h"
#include "../components/enemy_states.h"
#include "../components/cmp_menu.h"
#include "../score.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player; //Player Entity
sf::Texture spritesheet; //Player spritesheet
sf::Sprite playerSprite; //Player sprite

sf::Texture enemySheet;
sf::Sprite enemySprite;

sf::Texture asteroidSheet;
sf::Sprite asteroidSprite;

Texture backgroundtexture;	//Background spritesheet
Sprite backgroundSprite;	//Background sprite
static shared_ptr<Entity> walls[4];
sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f)); //View (camera) reference

static shared_ptr<Entity> timerText;
static shared_ptr<TextComponent> timerTextComponent;
static shared_ptr<Entity> waveText;
static shared_ptr<TextComponent> waveTextComponent;
static shared_ptr<Entity> scoreText;
static shared_ptr<TextComponent> scoreTextComponent;


MyContactListener listenerInstance;

sf::Sprite pauseMenu;

static shared_ptr<Entity> resumeButton; //Player Entity
static shared_ptr<Entity> restartButton; //Player Entity
static shared_ptr<Entity> exitButton; //Player Entity

void MainScene::Load() {
	_paused = false;


	Physics::GetWorld()->SetContactListener(&listenerInstance);
	cout << "" << endl;
	cout << "Controls: 1 for normal" << endl;
	cout << "Controls: 2 for heavy" << endl;
	cout << "Controls: 3 for beam (TODO)" << endl;
	cout << "Controls: 4 for triple shot" << endl;
	cout << "Controls: 5 for burst fire" << endl;
	cout << "Controls: 6 for shotgun" << endl;
	cout << "Controls: 7 for quick" << endl;
	cout << "" << endl;

	Vector2f walls[] = {
		// Top
		Vector2f((gameWidth * scale) * .5f, 5.f), Vector2f((gameWidth * scale), 10.f),
		// Bottom
		Vector2f((gameWidth * scale) * .5f, (gameHeight * scale) - 5.f), Vector2f((gameWidth * scale), 10.f),
		// left
		Vector2f(5.f, (gameHeight * scale) * .5f), Vector2f(10.f, (gameHeight * scale)),
		// right
		Vector2f((gameWidth * scale) - 5.f, (gameHeight * scale) * .5f), Vector2f(10.f, (gameHeight * scale))
	};
	for (int i = 0; i < 7; i += 2) {
		auto e = makeEntity();
		e->setPosition(walls[i]);
		auto s = e->addComponent<ShapeComponent>();

		if (i == 0) {
			s->setShape<sf::RectangleShape>(walls[i + 1]);
			s->getShape().setOrigin(walls[i + 1].x / 2, walls[i + 1].y / 2);
			s->getShape().setPosition({ gameWidth * scale, 0 });
			auto p = e->addComponent<PhysicsComponent>(false, Vector2f(gameWidth * scale, 10), constWALL, (short)(constPLAYER | constBULLET | constENEMY), &walls[i]);
		}
		else if (i == 2) {
			s->setShape<sf::RectangleShape>(walls[i + 1]);
			s->getShape().setOrigin(walls[i + 1].x / 2, walls[i + 1].y / 2);
			s->getShape().setPosition({ gameWidth * scale, gameHeight * scale });
			auto p = e->addComponent<PhysicsComponent>(false, Vector2f(gameWidth * scale, 10), constWALL, (short)(constPLAYER | constBULLET | constENEMY), &walls[i]);
		}
		else if (i == 4) {
			s->setShape<sf::RectangleShape>(walls[i + 1]);
			s->getShape().setOrigin(walls[i + 1].x / 2, walls[i + 1].y / 2);
			s->getShape().setPosition({ gameWidth * scale, gameHeight * scale });
			auto p = e->addComponent<PhysicsComponent>(false, Vector2f(10, gameHeight * scale), constWALL, (short)(constPLAYER | constBULLET | constENEMY), &walls[i]);
		}
		else if (i == 6) {
			s->setShape<sf::RectangleShape>(walls[i + 1]);
			s->getShape().setOrigin(walls[i + 1].x / 2, walls[i + 1].y / 2);
			s->getShape().setPosition({ gameWidth * scale, gameHeight * scale });
			auto p = e->addComponent<PhysicsComponent>(false, Vector2f(10, gameHeight * scale), constWALL, (short)(constPLAYER | constBULLET | constENEMY), &walls[i]);
		}
		s->getShape().setFillColor(Color::Cyan);
		e->addTag("wall");
		//e->addComponent<PhysicsComponent>(true, Vector2f(20, gameHeight * scale));
		//auto body = CreatePhysicsBox(*world, false, *s);
	}


	if (sf::Joystick::isConnected(0)) {
		cout << "Controller connected" << endl;
	}
	else if (!sf::Joystick::isConnected(0)) {
		cout << "No controller connected" << endl;

	}
	//Loads in player spritesheet and background sprite
	if (spritesheet.loadFromFile("res/SpriteSheet.png")) {
		player = makeEntity();				//create player entity
		player->setPosition({ (gameWidth * scale) / 2, (gameHeight * scale) / 2 });


		//sets player position to roughly centre screen
		auto s = player->addComponent<SpriteComponent>(); //Adds sprite component for sprite and animation handling
		auto p = player->addComponent<PlayerMovementComponent>(); //Adds movement component for x rotation
		auto f = player->addComponent<PlayerFireComponent>();	//Adds fire component for gun movement
		player->addTag("player");

		playerSprite.setTexture(spritesheet);
		p->setSpeed(100.f);
		s->setSprite<Sprite>(playerSprite);
		auto playerPhysics = player->addComponent<PhysicsComponent>(true, Vector2f(10.0f, 10.0f), constPLAYER, (short)(constWALL | constENEMY | constENEMYBULLET | constPICKUP), &player);
		auto rect = IntRect(0, 0, 1600, 1600); //One player ship is 1600, 1600. Spritesheet contains 4 health states
		s->getSprite().setTextureRect(rect);
		s->getSprite().setOrigin(800, 800);
		s->getSprite().setScale({ 0.05, 0.05 }); //scales down as texture is very large
	}
	if (backgroundtexture.loadFromFile("res/background.jpeg")) {
		backgroundSprite.setTexture(backgroundtexture);
		backgroundSprite.setOrigin(800, 450);
		backgroundSprite.setPosition((gameWidth * scale) / 2, (gameHeight * scale) / 2);
		backgroundSprite.setScale(scale, scale);

		pauseMenu.setPosition({ -1000, -1000 });
		pauseMenu.setTexture(backgroundtexture);
		pauseMenu.setOrigin({ 800,450 });
	}
	if (enemySheet.loadFromFile("res/enemySpritesheet.png")) {
		for (size_t i = 0; i < 1; i++)
		{
			createEnemyOrb();
			//createEnemyHarpoon();
			createEnemySpike();
		}
	}




	if (asteroidSheet.loadFromFile("res/asteroid_sheet.png"))
	{
		asteroidSprite.setTexture(asteroidSheet);
		auto asteroid = makeEntity();
		asteroid->setPosition({ 800,800 });
		asteroid->addTag("asteroid");
		auto s = asteroid->addComponent<SpriteComponent>();
		s->setSprite<Sprite>(asteroidSprite);
		auto rect = IntRect(0, 0, 850, 700);
		s->getSprite().setOrigin(400, 350);
		s->getSprite().setTextureRect(rect);
		s->getSprite().setScale({ 0.5, 0.5 });

		auto i = asteroid->addComponent<PhysicsComponent>(true, Vector2f(200.0f, 160.0f), constENEMY, (short)(constBULLET | constWALL | constPLAYER), &asteroid);
		//i->impulse({ 10,10 });
		//i->setRestitution(1);

	}
	//Simulate long loading times UNCOMMENT FOR RELEASE
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//cout << " Main scene Load Done" << endl;

	timerText = makeEntity();
	timerTextComponent = timerText->addComponent<TextComponent>("Wave timer");

	waveText = makeEntity();
	waveTextComponent = timerText->addComponent<TextComponent>("Wave 1");

	scoreText = makeEntity();
	scoreTextComponent = timerText->addComponent<TextComponent>("0");

	view.setSize(gameWidth / 3, gameHeight / 3); //sets size of camera
	view.zoom(3.f); //sets zoom for camera allowing animation
	Engine::GetWindow().setView(view); //sets window view to created view

	pauseMenu.setOrigin(gameWidth / 2, gameHeight / 2);

	resumeButton = makeEntity();
	resumeButton->addTag("resume");
	resumeButton->setPosition({ -1000, -1100 });
	resumeButton->addComponent<MenuItemComponent>("resume");

	restartButton = makeEntity();
	restartButton->addTag("restart");
	restartButton->setPosition({ -1000, -1000 });
	restartButton->addComponent<MenuItemComponent>("restart");

	exitButton = makeEntity();
	exitButton->addTag("home");
	exitButton->setPosition({ -1000, -900 });
	exitButton->addComponent<MenuItemComponent>("exit");

	if (music.getStatus() != 2)
	{
		if (!music.openFromFile("res/soundFX/main_music.WAV")) {
			cout << "error loading music" << endl;
		}
		else {
			music.setVolume(30);
			music.play();
			music.setLoop(true);
		}
	}

	setLoaded(true);


}

void MainScene::UnLoad() {
	cout << "Scene 1 Unload" << endl;
	player.reset();
	Scene::UnLoad();
}

void MainScene::Update(const double& dt) {
	// catch the resize events
	// catch the resize events
	sf::Event event;
	RenderWindow &window = Engine::GetWindow();
    while (window.pollEvent(event)) {
	  if (event.type == Event::Closed) {
	    window.close();
	  }
	}

	_keyboardCooldown -= dt;
	if (_keyboardCooldown < 0) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			_paused = !_paused;
			_keyboardCooldown = 0.5;
		}
	}
	if (!_paused) {
		clickCooldown -= dt;
		music.setVolume(50);
		sf::View currentView = Engine::GetWindow().getView();
		auto playerSprite = player->get_components<SpriteComponent>()[0];
		float leftCheck = playerSprite->getSprite().getPosition().x - (currentView.getSize().x / 2);
		float rightCheck = playerSprite->getSprite().getPosition().x + (currentView.getSize().x / 2);

		float topCheck = playerSprite->getSprite().getPosition().y - ((currentView.getSize().y / 2));

		float bottomCheck = playerSprite->getSprite().getPosition().y + ((currentView.getSize().y / 2));

		if (leftCheck >= 0 && rightCheck <= (gameWidth * scale)) {
			currentView.setCenter(playerSprite->getSprite().getPosition().x, currentView.getCenter().y);
		}
		if (topCheck >= 0 && bottomCheck <= (gameHeight * scale)) {
			currentView.setCenter(currentView.getCenter().x, playerSprite->getSprite().getPosition().y);
		}

		Engine::GetWindow().setView(currentView);

		Vector2f topLeft = { (currentView.getCenter().x - (currentView.getSize().x / 2) + 50), (currentView.getCenter().y - (currentView.getSize().y / 2) + 20) };
		Vector2f topRight = { (currentView.getCenter().x + (currentView.getSize().x / 2) - 150), (currentView.getCenter().y - (currentView.getSize().y / 2) + 20) };
		Vector2f topMiddle = { (currentView.getCenter().x), (currentView.getCenter().y) - (currentView.getSize().y / 2) + 20 };
		timerTextComponent->SetPosition(topLeft);
		waveTextComponent->SetPosition(topRight);
		scoreTextComponent->SetPosition(topMiddle);

		_wavetimer -= dt;
		string str = to_string(_wavetimer);
		str.resize(str.size() - 5);
		timerTextComponent->SetText(str);

		str = (to_string(score.getScore()));
		str.resize(str.size() - 7);
		scoreTextComponent->SetText(str);

		if (_wavetimer < 0)//SPAWNING WAVES
		{
			_wavetimer = 5;
			_wavenumber++;
			string wavenum = to_string(_wavenumber);
			wavenum = "Wave " + wavenum;
			wavenum.resize(wavenum.size() - 7);
			waveTextComponent->SetText(wavenum);
			//random_device dev;
			//default_random_engine engine(dev());
			//uniform_real_distribution<float> x_dist(0.0f,
			//	Engine::GetWindow().getSize().x);
			//uniform_real_distribution<float> y_dist(0.0f,
			//	Engine::GetWindow().getSize().y);
			//auto enemy = makeEntity();
			//enemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
			//auto e = enemy->addComponent<SpriteComponent>();
			//e->setSprite<Sprite>(enemySprite);
			//e->getSprite().setOrigin(800, 800);
			//e->getSprite().setScale({ 0.05, 0.05 });
			//enemy->addComponent<SteeringComponent>(player.get());
		}
		Scene::Update(dt);
	}
	else if (_paused) {
		music.setVolume(25);
		resumeButton->update(dt);
		restartButton->update(dt);
		exitButton->update(dt);
	}
}

void MainScene::Render() {
	Renderer::queue(&backgroundSprite);
	if (_paused) {
		sf::View pauseView = Engine::GetWindow().getView();
		pauseView.setCenter({ -1000, -1000 });
		Engine::GetWindow().setView(pauseView);
		Renderer::queue(&pauseMenu);

	}
	Scene::Render();
}


void MainScene::createEnemyOrb() {

	enemySprite.setTexture(enemySheet);

	random_device dev;
	default_random_engine engine(dev());
	uniform_real_distribution<float> x_dist(0.0f,
		Engine::GetWindow().getSize().x * scale);
	uniform_real_distribution<float> y_dist(0.0f,
		Engine::GetWindow().getSize().y* scale);


	auto enemy = makeEntity();
	enemy->addTag("enemy");

	enemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
	auto e = enemy->addComponent<SpriteComponent>();
	e->setSprite<Sprite>(enemySprite);
	e->getSprite().setOrigin(800, 800);
	e->getSprite().setScale({ 0.05, 0.05 });
	
	auto rect = IntRect(0, 0, 1600, 1600); //One player ship is 1600, 1600. Spritesheet contains 4 health states
	e->getSprite().setTextureRect(rect);
	enemy->addComponent<SteeringComponent>(player.get(), 300.0f);
	
	
	auto enemyComponent = enemy->addComponent<EnemyComponent>();
	enemyComponent->setHealth(2);

	auto phys = enemy->addComponent<PhysicsComponent>(true, Vector2f(40.0f, 40.0f), constENEMY, (short)(constBULLET | constPLAYER | constENEMY | constWALL), &enemy);


}

void MainScene::createEnemyHarpoon() {

	enemySprite.setTexture(enemySheet);

	random_device dev;
	default_random_engine engine(dev());
	uniform_real_distribution<float> x_dist(0.0f,
		Engine::GetWindow().getSize().x * scale);
	uniform_real_distribution<float> y_dist(0.0f,
		Engine::GetWindow().getSize().y* scale);


	auto enemy = makeEntity();
	enemy->addTag("enemy");

	enemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
	auto e = enemy->addComponent<SpriteComponent>();
	e->setSprite<Sprite>(enemySprite);
	e->getSprite().setOrigin(800, 800);
	e->getSprite().setScale({ 0.05, 0.05 });
	auto rect = IntRect(1600, 0, 1600, 1600); //One player ship is 1600, 1600. Spritesheet contains 4 health state
	e->getSprite().setTextureRect(rect);
	enemy->addComponent<SteeringComponent>(player.get(), 300.0f);
	auto enemyComponent = enemy->addComponent<EnemyComponent>();
	enemyComponent->setHealth(5);

	auto phys = enemy->addComponent<PhysicsComponent>(true, Vector2f(40.0f, 40.0f), constENEMY, (short)(constBULLET | constPLAYER | constENEMY | constWALL), &enemy);



}

void MainScene::createEnemySpike() {

	enemySprite.setTexture(enemySheet);


	random_device dev;
	default_random_engine engine(dev());
	uniform_real_distribution<float> x_dist(0.0f,
		Engine::GetWindow().getSize().x * scale);
	uniform_real_distribution<float> y_dist(0.0f,
		Engine::GetWindow().getSize().y* scale);


	auto enemy = makeEntity();
	enemy->addTag("enemy");

	enemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
	auto e = enemy->addComponent<SpriteComponent>();
	e->setSprite<Sprite>(enemySprite);
	e->getSprite().setOrigin(800, 800);
	e->getSprite().setScale({ 0.05, 0.05 });
	auto rect = IntRect(3200, 0, 1600, 1600); //One player ship is 1600, 1600. Spritesheet contains 4 health state
	e->getSprite().setTextureRect(rect);
	enemy->addComponent<SteeringComponent>(player.get(), 300.0f);
	auto enemyComponent = enemy->addComponent<EnemyComponent>();
	enemyComponent->setHealth(4);

	auto phys = enemy->addComponent<PhysicsComponent>(true, Vector2f(40.0f, 40.0f), constENEMY, (short)(constBULLET | constPLAYER | constENEMY | constWALL), &enemy);


}
