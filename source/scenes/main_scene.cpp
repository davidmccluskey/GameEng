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
sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f)); //View (camera) reference]

void MainScene::Load() {
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
		switch (i) {
		case 0:
			s->setShape<sf::RectangleShape>(walls[i + 1]);
			s->getShape().setOrigin(walls[i + 1].x / 2, walls[i + 1].y / 2);
			s->getShape().setPosition({ gameWidth * scale, 0});
			e->addComponent<PhysicsComponent>(false, Vector2f(gameWidth * scale, 10));
			break;
		case 2:
			s->setShape<sf::RectangleShape>(walls[i + 1]);
			s->getShape().setOrigin(walls[i + 1].x / 2, walls[i + 1].y / 2);
			s->getShape().setPosition({ gameWidth * scale, gameHeight * scale });
			e->addComponent<PhysicsComponent>(false, Vector2f(gameWidth * scale, 10));
			break;
		case 4:
			s->setShape<sf::RectangleShape>(walls[i + 1]);
			s->getShape().setOrigin(walls[i + 1].x / 2, walls[i + 1].y / 2);
			s->getShape().setPosition({ gameWidth * scale, gameHeight * scale });
			e->addComponent<PhysicsComponent>(false, Vector2f(10, gameHeight * scale));
			break;
		case 6:
			s->setShape<sf::RectangleShape>(walls[i + 1]);
			s->getShape().setOrigin(walls[i + 1].x / 2, walls[i + 1].y / 2);
			s->getShape().setPosition({ gameWidth * scale, gameHeight * scale });
			e->addComponent<PhysicsComponent>(false, Vector2f(10, gameHeight * scale));
			break;
		}
		s->getShape().setFillColor(Color::Magenta);
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
		playerSprite.setTexture(spritesheet);
		p->setSpeed(100.f);
		s->setSprite<Sprite>(playerSprite);
		auto i = player->addComponent<PhysicsComponent>(true, Vector2f(10.0f, 10.0f));
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
	}
	if (enemySheet.loadFromFile("res/enemy_orb.png")) {
		enemySprite.setTexture(enemySheet);

		for (size_t n = 0; n < 2; ++n) {
			random_device dev;
			default_random_engine engine(dev());
			uniform_real_distribution<float> x_dist(0.0f,
				Engine::GetWindow().getSize().x);
			uniform_real_distribution<float> y_dist(0.0f,
				Engine::GetWindow().getSize().y);

			auto enemy = makeEntity();
			enemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
			auto e = enemy->addComponent<SpriteComponent>();
			e->setSprite<Sprite>(enemySprite);
			e->getSprite().setOrigin(800, 800);
			e->getSprite().setScale({ 0.05, 0.05 });
			enemy->addComponent<SteeringComponent>(player.get());

			auto i = enemy->addComponent<PhysicsComponent>(true, Vector2f(40.0f, 40.0f));
		}
	}

	if (asteroidSheet.loadFromFile("res/asteroid_sheet.png"))
	{
		asteroidSprite.setTexture(asteroidSheet);
		auto asteroid = makeEntity();
		asteroid->setPosition({ 800,800 });

		auto s = asteroid->addComponent<SpriteComponent>();
		s->setSprite<Sprite>(asteroidSprite);
		auto rect = IntRect(0, 0, 850, 700);
		s->getSprite().setOrigin(400, 350);
		s->getSprite().setTextureRect(rect);
		s->getSprite().setScale({ 0.5, 0.5 });

		auto i = asteroid->addComponent<PhysicsComponent>(true, Vector2f(270.0f, 200.0f));
		i->impulse({ 10,10 });
		i->setRestitution(1);

	}
	//Simulate long loading times UNCOMMENT FOR RELEASE
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//cout << " Main scene Load Done" << endl;


	view.setSize(gameWidth / 2, gameHeight / 2); //sets size of camera
	view.zoom(5.0f); //sets zoom for camera allowing animation
	Engine::GetWindow().setView(view); //sets window view to created view
	setLoaded(true);
}

void MainScene::UnLoad() {
	cout << "Scene 1 Unload" << endl;
	player.reset();
	Scene::UnLoad();
}

void MainScene::Update(const double& dt) {
	Scene::Update(dt);
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
	//_wavetimer -= dt;

	//if (_wavetimer < 0)//SPAWNING WAVES
	//{
	//	_wavetimer = 5;
	//	_wavenumber++;

	//	cout << "wave spawned" << endl;
	//	cout << _wavenumber << endl;

	//	random_device dev;
	//	default_random_engine engine(dev());
	//	uniform_real_distribution<float> x_dist(0.0f,
	//		Engine::GetWindow().getSize().x);
	//	uniform_real_distribution<float> y_dist(0.0f,
	//		Engine::GetWindow().getSize().y);
	//	auto enemy = makeEntity();
	//	enemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
	//	auto e = enemy->addComponent<SpriteComponent>();
	//	e->setSprite<Sprite>(enemySprite);
	//	e->getSprite().setOrigin(800, 800);
	//	e->getSprite().setScale({ 0.05, 0.05 });
	//	enemy->addComponent<SteeringComponent>(player.get());
	//}
}

void MainScene::Render() {
	Renderer::queue(&backgroundSprite);
	//for (auto& p : walls) {
	//	Renderer::queue(&p);
	//}


	Scene::Render();
}
