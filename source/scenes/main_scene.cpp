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

sf::Texture enemySheet; //Player spritesheet
sf::Sprite enemySprite; //Player sprite

Texture backgroundtexture;	//Background spritesheet
Sprite backgroundSprite;	//Background sprite
RectangleShape walls[4];
sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f)); //View (camera) reference]

void MainScene::Load() {

	cout << "Controls: 1 for normal" << endl;
	cout << "Controls: 2 for heavy" << endl;
	cout << "Controls: 3 for beam (TODO)" << endl;
	cout << "Controls: 4 for triple shot" << endl;
	cout << "Controls: 5 for burst fire" << endl;
	cout << "Controls: 6 for shotgun" << endl;
	cout << "Controls: 7 for quick" << endl;

	walls[0].setSize({ 20, gameHeight * scale});
	walls[1].setSize({ 20, gameHeight * scale});
	walls[2].setSize({ gameWidth * scale, 20 });
	walls[3].setSize({ gameWidth * scale, 20 });

	walls[0].setOrigin({ 10, gameHeight * scale});
	walls[0].setPosition({ gameWidth * scale, gameHeight * scale});
	walls[2].setOrigin({ gameWidth * scale, 10 });
	walls[2].setPosition({ gameWidth * scale, gameHeight * scale });

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
		auto i = player->addComponent<PhysicsComponent>(true, Vector2f(0.0f, 0.0f));
		auto rect = IntRect(0, 0, 1600, 1600); //One player ship is 1600, 1600. Spritesheet contains 4 health states

		s->getSprite().setTextureRect(rect);
		s->getSprite().setOrigin(800, 800);
		s->getSprite().setScale({ 0.05, 0.05 }); //scales down as texture is very large
		s->getSprite().setPosition({ 400 * scale,400 * scale });

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
		}
	}

	cout << player->getPosition() << endl;

	//Simulate long loading times UNCOMMENT FOR RELEASE
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//cout << " Main scene Load Done" << endl;


	view.setSize(gameWidth/2, gameHeight/2); //sets size of camera
	view.zoom(2.0f); //sets zoom for camera allowing animation
	Engine::GetWindow().setView(view); //sets window view to created view
	setLoaded(true);

	cout << player->getPosition() << endl;
}

void MainScene::UnLoad() {
	cout << "Scene 1 Unload" << endl;
	player.reset();
	Scene::UnLoad();
}

void MainScene::Update(const double& dt) {
	Scene::Update(dt);
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
	for (auto& p : walls) {
		Renderer::queue(&p);
	}


	Scene::Render();
}
