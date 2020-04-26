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
#include "../options.h"
#include "../texture.h"
#include "../sounds.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

//Sprites
sf::Sprite enemySprite;
Sprite backgroundSprite;	
static shared_ptr<Entity> walls[4];
sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f)); //View (camera) reference

static shared_ptr<Entity> timerText;
static shared_ptr<TextComponent> timerTextComponent;
static shared_ptr<Entity> waveText;
static shared_ptr<TextComponent> waveTextComponent;
static shared_ptr<Entity> scoreText;
static shared_ptr<TextComponent> scoreTextComponent;

static shared_ptr<Entity> healthText;
static shared_ptr<TextComponent> healthTextComponent;

static shared_ptr<Entity> partOne;
static shared_ptr<Entity> partTwo;
static shared_ptr<Entity> partThree;
static shared_ptr<Entity> partFour;
static shared_ptr<Entity> partFive;

Sprite spriteOne;
Sprite spriteTwo;
Sprite spriteThree;
Sprite spriteFour;
Sprite spriteFive;

float healthMultiplier = 1;

MyContactListener listenerInstance;

sf::Sprite pauseMenu;

static shared_ptr<Entity> resumeButton; //Player Entity
static shared_ptr<Entity> restartButton; //Player Entity
static shared_ptr<Entity> exitButton; //Player Entity

bool playerDeadSpawned = false;
double endTimer = 3;
double baseWaveNum = 20;
int enemySpawns = 1;
bool _isDead = false;
int viewX;
int viewY;
void MainScene::Load() {
	windowWidth = Options::instance()->launchWidth;
	windowHeight = Options::instance()->launchHeight;
	reset();

	float scaleWidth = windowWidth / 1600;
	float scaleHeight = windowHeight / 900;

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

	{
		//Loads in player spritesheet and background sprite
		player = makeEntity();				//create player entity
		player->setPosition({ (gameWidth * scale) / 2, (gameHeight * scale) / 2 });
		//sets player position to roughly centre screen
		auto s = player->addComponent<SpriteComponent>(); //Adds sprite component for sprite and animation handling
		auto p = player->addComponent<PlayerMovementComponent>(); //Adds movement component for x rotation
		auto f = player->addComponent<PlayerFireComponent>();	//Adds fire component for gun movement
		f->setAsNormal();
		player->addTag("player");
		sf::Sprite playerSprite;
		playerSprite.setTexture(Textures::instance()->getPlayerStates());
		p->setSpeed(100.f);
		s->setSprite<Sprite>(playerSprite);
		auto playerPhysics = player->addComponent<PhysicsComponent>(true, Vector2f(10.0f, 10.0f), constPLAYER, (short)(constWALL | constENEMY | constENEMYBULLET | constPICKUP), &player);
		auto rect = IntRect(0, 0, 1600, 1600); //One player ship is 1600, 1600. Spritesheet contains 4 health states
		s->getSprite().setTextureRect(rect);
		s->getSprite().setOrigin(800, 800);
		s->getSprite().setScale({ 0.05, 0.05 }); //scales down as texture is very large
	}

	{
		backgroundSprite.setTexture(Textures::instance()->getBackground());
		backgroundSprite.setOrigin(0, 0);
		backgroundSprite.setPosition(0, 0);
		backgroundSprite.setScale(scaleWidth * scale, scaleHeight * scale);

		pauseMenu.setPosition({ -windowWidth, -windowHeight });
		pauseMenu.setTexture(Textures::instance()->getBackground());
		pauseMenu.setOrigin({ 0,0 });
		pauseMenu.setScale(scaleWidth, scaleHeight);
	}


	{
		//asteroidSprite.setTexture(Textures::instance()->getAstroid());
		//auto asteroid = makeEntity();
		//asteroid->setPosition({ 800,800 });
		//asteroid->addTag("asteroid");
		//auto s = asteroid->addComponent<SpriteComponent>();
		//s->setSprite<Sprite>(asteroidSprite);
		//auto rect = IntRect(0, 0, 850, 700);
		//s->getSprite().setOrigin(400, 350);
		//s->getSprite().setTextureRect(rect);
		//s->getSprite().setScale({ 0.5, 0.5 });

		//auto i = asteroid->addComponent<PhysicsComponent>(true, Vector2f(200.0f, 160.0f), constENEMY, (short)(constBULLET | constWALL | constPLAYER), &asteroid);
	}

	timerText = makeEntity();
	timerTextComponent = timerText->addComponent<TextComponent>("Wave timer");

	waveText = makeEntity();
	waveTextComponent = timerText->addComponent<TextComponent>("Wave 1");

	scoreText = makeEntity();
	scoreTextComponent = timerText->addComponent<TextComponent>("0");

	if (Options::instance()->altHealthIndicator == 1) {
		healthText = makeEntity();
		healthTextComponent = timerText->addComponent<TextComponent>("Health 4");
	}

	view.setSize(gameWidth / 3, gameHeight / 3); //sets size of camera
	view.zoom(3.f); //sets zoom for camera allowing animation
	Engine::GetWindow().setView(view); //sets window view to created view
	//prevView.setCenter(view.getCenter());

	resumeButton = makeEntity();
	resumeButton->addTag("resume");
	resumeButton->setPosition({ -(windowWidth / 2) , -(windowHeight / 2) - 100 });
	resumeButton->addComponent<MenuItemComponent>("resume");

	restartButton = makeEntity();
	restartButton->addTag("restart");
	restartButton->setPosition({ -(windowWidth / 2) , -(windowHeight / 2) });
	restartButton->addComponent<MenuItemComponent>("restart");

	exitButton = makeEntity();
	exitButton->addTag("home");
	exitButton->setPosition({ -(windowWidth / 2) , -(windowHeight / 2) + 100 });
	exitButton->addComponent<MenuItemComponent>("exit");

	if (Options::instance()->musicOn) {
		if (music.getStatus() != 2)
		{
			if (!music.openFromFile("res/soundFX/main_music.WAV")) {
				cout << "error loading music" << endl;
			}
			else {
				music.setVolume(Options::instance()->volume);
				music.play();
				music.setLoop(true);
			}
		}
	}
	//createEnemyOrb();
	//createEnemyHarpoon();
	//createEnemySmall();
	//createEnemySpike();
	setLoaded(true);

}

void MainScene::UnLoad() {
	cout << "Scene 1 Unload" << endl;
	player.reset();
	partOne.reset();
	partTwo.reset();
	partThree.reset();
	partFour.reset();
	partFive.reset();
	exitButton.reset();
	restartButton.reset();
	resumeButton.reset();
	timerText.reset();
	waveText.reset();
	healthText.reset();
	Scene::UnLoad();
}

void MainScene::Update(const double& dt) {
	//cout << "on scren " << _enemyNum << endl;
	// catch the resize events
	// catch the resize events

	_keyboardCooldown -= dt;
	if (_keyboardCooldown < 0) {
		if (Keyboard::isKeyPressed(Keyboard::Key(Options::instance()->pauseKey))) {
			_paused = !_paused;
			_keyboardCooldown = 0.5;
		}
	}
	if (!_paused) {
		clickCooldown -= dt;
		music.setVolume(Options::instance()->volume);
		sf::View currentView = Engine::GetWindow().getView();
		//currentView.zoom(3.f);
		auto playerSprite = player->get_components<SpriteComponent>()[0];
		float leftCheck = playerSprite->getSprite().getPosition().x - (currentView.getSize().x / 2);
		float rightCheck = playerSprite->getSprite().getPosition().x + (currentView.getSize().x / 2);

		float topCheck = playerSprite->getSprite().getPosition().y - ((currentView.getSize().y / 2));

		float bottomCheck = playerSprite->getSprite().getPosition().y + ((currentView.getSize().y / 2));

		if (leftCheck >= 0 && rightCheck <= (gameWidth * scale)) {
			currentView.setCenter(playerSprite->getSprite().getPosition().x, currentView.getCenter().y);
			viewX = currentView.getCenter().x;
		}
		else {
			currentView.setCenter(viewX, viewY);
		}
		if (topCheck >= 0 && bottomCheck <= (gameHeight * scale)) {
			currentView.setCenter(currentView.getCenter().x, playerSprite->getSprite().getPosition().y);
			viewY = currentView.getCenter().y;
			//prevView.setCenter(currentView.getCenter().x, playerSprite->getSprite().getPosition().y);
		}
		else {
			currentView.setCenter(viewX, viewY);
		}

		Engine::GetWindow().setView(currentView);

		Vector2f topLeft = { (currentView.getCenter().x - (currentView.getSize().x / 2) + 50), (currentView.getCenter().y - (currentView.getSize().y / 2) + 20) };
		Vector2f topRight = { (currentView.getCenter().x + (currentView.getSize().x / 2) - 150), (currentView.getCenter().y - (currentView.getSize().y / 2) + 20) };
		Vector2f topMiddle = { (currentView.getCenter().x), (currentView.getCenter().y) - (currentView.getSize().y / 2) + 20 };
		Vector2f bottomRight = { (currentView.getCenter().x + (currentView.getSize().x / 2) - 200), (currentView.getCenter().y + (currentView.getSize().y / 2) - 50) };

		timerTextComponent->SetPosition(topLeft);
		waveTextComponent->SetPosition(topRight);
		scoreTextComponent->SetPosition(topMiddle);

		if (Options::instance()->altHealthIndicator == 1) {
			auto mvmt = player->get_components<PlayerMovementComponent>()[0];
			int health = mvmt->getHealth();
			string str = "health: " + to_string(health);
			healthTextComponent->SetText(str);
			healthTextComponent->SetPosition(bottomRight);
		}

		if (_isDead != true) {
			_wavetimer -= dt;
			string str = to_string(_wavetimer);
			str.resize(str.size() - 5);
			timerTextComponent->SetText(str);

			str = (to_string(score.getScore()));
			str.resize(str.size() - 7);
			scoreTextComponent->SetText(str);

			if (_wavetimer < 0 || _enemyNum <= 0)//SPAWNING WAVES
			{
				cout << healthMultiplier << endl;
				if (_wavenumber > 20) { //Health multiplier only increases after level 20
					healthMultiplier = healthMultiplier + 0.2;
				}
				score.setScore(1000);

				if (baseWaveNum - 1 != 5) {
					_wavetimer = baseWaveNum;
					baseWaveNum -= 0.5;
				}
				else {
					_wavetimer = 5;
				}
				int enemyCheck = enemySpawns;
				_wavenumber++;

				if (enemyCheck + 1 <= 10) {
					if (_wavenumber % 2 == 0) {
						enemySpawns++;
					}
				}
				if (_wavenumber % 10 == 0) {	//Boss every 10 waves
					createEnemyBoss();
					enemySpawns++;
				}

				string wavenum = to_string(_wavenumber);
				wavenum = "Wave " + wavenum;
				waveTextComponent->SetText(wavenum);

				createEnemyBoss();
				/*for (int i = 0; i < enemySpawns; i++) {
					int enemyType = rand() % 4 + 1;
					switch (enemyType) {
					case 1:
						createEnemyHarpoon();
						break;
					case 2:
						createEnemyOrb();
						break;
					case 3:
						createEnemySpike();
						break;
					case 4:
						createEnemySmall();
						break;
					}*/
				/*}*/
				cout << "spawned " << enemySpawns << endl;
			}
		}
		else {
			DeathResolution(dt);
			spawnDeadPlayer();
		}
		Scene::Update(dt);
		sf::Event event;
		RenderWindow& window = Engine::GetWindow();
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
	}
	else if (_paused) {
		music.setVolume(Options::instance()->volume / 2);
		resumeButton->update(dt);
		restartButton->update(dt);
		exitButton->update(dt);

		sf::View pauseView = Engine::GetWindow().getDefaultView();
		pauseView.setCenter({ -(windowWidth / 2), -(windowHeight / 2) });
		Engine::GetWindow().setView(pauseView);
	}
}

void MainScene::Render() {
	Renderer::queue(&backgroundSprite);
	if (_paused) {
		Renderer::queue(&pauseMenu);

	}
	Scene::Render();
}


void MainScene::createEnemyOrb() {
	_enemyNum++;
	enemySprite.setTexture(Textures::instance()->getEnemyAnimations());
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> xDist(1, (gameWidth * scale) - 100);
	int xVal = xDist(generator);

	std::uniform_int_distribution<int> yDist(1, (gameHeight * scale) - 100);
	int yVal = yDist(generator);
	cout << xVal << ", " << yVal << endl;

	auto enemy = makeEntity();
	enemy->addTag("enemy");
	enemy->addTag("orb");

	enemy->setPosition(Vector2f(xVal, yVal));
	auto e = enemy->addComponent<SpriteComponent>();
	e->setSprite<Sprite>(enemySprite);
	e->getSprite().setOrigin(85, 142);
	e->getSprite().setScale({ 0.4, 0.4 });
	auto rect = IntRect(0, 0, 200, 300);
	e->getSprite().setTextureRect(rect);
	enemy->addComponent<SteeringComponent>(player.get(), 300.0f);


	auto enemyComponent = enemy->addComponent<EnemyComponent>();
	enemyComponent->setHealth(3 * healthMultiplier);
	enemyComponent->setTextureSize(200, 285, 0);

	float min = gameHeight * 0.15;
	float max = min + 200;
	enemyComponent->setMinMax(min, max);

	auto phys = enemy->addComponent<PhysicsComponent>(true, Vector2f(40.0f, 40.0f), constENEMY, (short)(constBULLET | constPLAYER | constENEMY | constWALL), &enemy);
	enemyComponent->setFireDelay(1.5f);
}

void MainScene::createEnemyHarpoon() {
	_enemyNum++;
	enemySprite.setTexture(Textures::instance()->getEnemyAnimations());
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> xDist(1, (gameWidth * scale) - 100);
	int xVal = xDist(generator);

	std::uniform_int_distribution<int> yDist(1, (gameHeight * scale) - 100);
	int yVal = yDist(generator);
	cout << xVal << ", " << yVal << endl;

	auto enemy = makeEntity();
	enemy->addTag("enemy");
	enemy->addTag("harpoon");
	enemy->setPosition(Vector2f(xVal, yVal));
	auto e = enemy->addComponent<SpriteComponent>();
	e->setSprite<Sprite>(enemySprite);
	e->getSprite().setOrigin(85, 142);
	e->getSprite().setScale({ 0.4, 0.4 });

	auto rect = IntRect(0, 300, 200, 300);

	e->getSprite().setTextureRect(rect);
	enemy->addComponent<SteeringComponent>(player.get(), 300.0f);
	auto enemyComponent = enemy->addComponent<EnemyComponent>();
	enemyComponent->setHealth(10 * healthMultiplier);
	enemyComponent->setMinMax(500.0f, 700.0f);
	enemyComponent->setTextureSize(200, 285, 1);

	auto phys = enemy->addComponent<PhysicsComponent>(true, Vector2f(40.0f, 40.0f), constENEMY, (short)(constBULLET | constPLAYER | constENEMY | constWALL), &enemy);

	float min = gameHeight * 0.3;
	float max = min + 200;
	enemyComponent->setMinMax(min, max);
	enemyComponent->setFireDelay(2.0f);

}

void MainScene::createEnemySpike() {
	_enemyNum++;

	enemySprite.setTexture(Textures::instance()->getEnemyAnimations());
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> xDist(1, (gameWidth * scale) - 100);
	int xVal = xDist(generator);

	std::uniform_int_distribution<int> yDist(1, (gameHeight * scale) - 100);
	int yVal = yDist(generator);
	cout << xVal << ", " << yVal << endl;

	auto enemy = makeEntity();
	enemy->addTag("enemy");
	enemy->addTag("spike");

	enemy->setPosition(Vector2f(xVal, yVal));
	auto e = enemy->addComponent<SpriteComponent>();
	e->setSprite<Sprite>(enemySprite);
	e->getSprite().setOrigin(85, 142);
	e->getSprite().setScale({ 0.4, 0.4 });
	auto rect = IntRect(0, 600, 200, 300);
	e->getSprite().setTextureRect(rect);
	enemy->addComponent<SteeringComponent>(player.get(), 300.0f);
	auto enemyComponent = enemy->addComponent<EnemyComponent>();
	enemyComponent->setHealth(4 * healthMultiplier);
	enemyComponent->setTextureSize(200, 285, 2);

	auto phys = enemy->addComponent<PhysicsComponent>(true, Vector2f(40.0f, 40.0f), constENEMY, (short)(constBULLET | constPLAYER | constENEMY | constWALL), &enemy);

	enemy->addTag("spike");

	float min = gameHeight * 0.15;
	float max = min + 200;
	enemyComponent->setMinMax(min, max);
}
void MainScene::createEnemySmall() {

	enemySprite.setTexture(Textures::instance()->getEnemyAnimations());
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> xDist(1, (gameWidth * scale) - 100);
	int xVal = xDist(generator);

	std::uniform_int_distribution<int> yDist(1, (gameHeight * scale) - 100);
	int yVal = yDist(generator);
	cout << xVal << ", " << yVal << endl;

	auto enemy = makeEntity();
	enemy->addTag("enemy");
	enemy->addTag("small");
	enemy->setPosition(Vector2f(xVal, yVal));
	auto e = enemy->addComponent<SpriteComponent>();
	e->setSprite<Sprite>(enemySprite);
	e->getSprite().setOrigin(85, 142);
	e->getSprite().setScale({ 0.4, 0.4 });
	auto rect = IntRect(0, 900, 200, 300);
	e->getSprite().setTextureRect(rect);
	enemy->addComponent<SteeringComponent>(player.get(), 400.0f);
	auto enemyComponent = enemy->addComponent<EnemyComponent>();
	enemyComponent->setHealth(4 * healthMultiplier);
	auto phys = enemy->addComponent<PhysicsComponent>(true, Vector2f(40.0f, 40.0f), constENEMY, (short)(constBULLET | constPLAYER | constENEMY | constWALL), &enemy);

	float min = gameHeight * 0.15;
	float max = min + 100;
	enemyComponent->setMinMax(min, max);

	_enemyNum++;
	enemyComponent->setTextureSize(200, 300, 2);
	enemyComponent->setFireDelay(0.6f);
}

void MainScene::createEnemyBoss() {
	Sounds::instance()->playBoss();
	enemySprite.setTexture(Textures::instance()->getEnemyAnimations());
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> xDist(1, (gameWidth * scale) - 100);
	int xVal = xDist(generator);

	std::uniform_int_distribution<int> yDist(1, (gameHeight * scale) - 100);
	int yVal = yDist(generator);
	cout << xVal << ", " << yVal << endl;

	auto enemy = makeEntity();
	enemy->addTag("enemy");
	enemy->addTag("finalBoss");
	enemy->setPosition(Vector2f(xVal, yVal));
	auto e = enemy->addComponent<SpriteComponent>();
	e->setSprite<Sprite>(enemySprite);
	e->getSprite().setOrigin(100, 50);
	e->getSprite().setScale({ 1.5, 1.5 });
	auto rect = IntRect(0, 1200, 200, 300);
	e->getSprite().setTextureRect(rect);
	enemy->addComponent<SteeringComponent>(player.get(), 300.0f);
	auto enemyComponent = enemy->addComponent<EnemyComponent>();
	enemyComponent->setHealth(40 * healthMultiplier);
	auto phys = enemy->addComponent<PhysicsComponent>(true, Vector2f(200.0f, 100.0f), constENEMY, (short)(constBULLET | constPLAYER | constENEMY | constWALL), &enemy);

	float min = gameHeight * 0.35;
	float max = min + 300;
	enemyComponent->setMinMax(min, max);

	_enemyNum++;
	enemyComponent->setTextureSize(200, 300, 2);
	enemyComponent->setFireDelay(9999990.35f);

}



void MainScene::reset() {
	_paused = false;
	score.resetScore();
	_wavetimer = 0;
	_wavenumber = 0;
	healthMultiplier = 1;
	baseWaveNum = 20;
	enemySpawns = 1;
	_isDead = false;
	endTimer = 3;
	playerDeadSpawned = false;
}

void MainScene::DeathResolution(float dt) {
	endTimer -= dt;
	if (endTimer <= 0) {
		Engine::ChangeScene(&scene_enter_highscore);
	}
}

void MainScene::spawnDeadPlayer() {
	if (playerDeadSpawned == false) {

		auto playerSprite = player->get_components<SpriteComponent>()[0];

		spriteOne.setTexture(Textures::instance()->getplayerdead());
		spriteTwo.setTexture(Textures::instance()->getplayerdead());
		spriteThree.setTexture(Textures::instance()->getplayerdead());
		spriteFour.setTexture(Textures::instance()->getplayerdead());
		spriteFive.setTexture(Textures::instance()->getplayerdead());

		partOne = makeEntity();
		partOne->setPosition(player->getPosition());

		partTwo = makeEntity();
		partTwo->setPosition(player->getPosition());

		partThree = makeEntity();
		partThree->setPosition(player->getPosition());

		partFour = makeEntity();
		partFour->setPosition(player->getPosition());

		partFive = makeEntity();
		partFive->setPosition(player->getPosition());


		{
			auto s = partOne->addComponent<SpriteComponent>();
			s->setSprite<Sprite>(spriteOne);
			s->getSprite().setScale(0.4, 0.4);
			s->getSprite().setOrigin(100, 100);
			s->getSprite().setTextureRect(IntRect(0, 0, 200, 200));
			s->getSprite().setRotation(playerSprite->getSprite().getRotation());

			Vector2f impulse = sf::rotate(Vector2f(0, 10.f), playerSprite->getSprite().getRotation());
			impulse = Vector2f(-impulse.x * 0.1, impulse.y * 0.1 );
			auto p = partOne->addComponent<PhysicsComponent>(true, Vector2f(10.0f, 10.0f), constPLAYER, (short)(constWALL | constENEMY | constENEMYBULLET | constPICKUP), &partOne);
			p->impulse(Vector2f(impulse));
			partOne->addTag("part");
		}
		{
			auto s = partTwo->addComponent<SpriteComponent>();
			s->setSprite<Sprite>(spriteTwo);
			s->getSprite().setScale(0.4, 0.4);
			s->getSprite().setOrigin(100, 100);
			s->getSprite().setTextureRect(IntRect(200, 0, 200, 200));
			s->getSprite().setRotation(playerSprite->getSprite().getRotation());
			partTwo->addTag("part");

			Vector2f impulse = sf::rotate(Vector2f(0, 5.f), playerSprite->getSprite().getRotation());
			impulse = Vector2f(-impulse.x * 0.1, 0);
			auto p = partTwo->addComponent<PhysicsComponent>(true, Vector2f(10.0f, 10.0f), constPLAYER, (short)(constWALL | constENEMY | constENEMYBULLET | constPICKUP), &partTwo);
			p->impulse(Vector2f(impulse));

		}
		{
			auto s = partThree->addComponent<SpriteComponent>();
			s->setSprite<Sprite>(spriteThree);
			s->getSprite().setScale(0.4, 0.4);
			s->getSprite().setOrigin(100, 100);
			s->getSprite().setTextureRect(IntRect(400, 0, 200, 200));
			s->getSprite().setRotation(playerSprite->getSprite().getRotation());
			partThree->addTag("part");

			Vector2f impulse = sf::rotate(Vector2f(0, 5.f), playerSprite->getSprite().getRotation());
			impulse = Vector2f(0, 0);
			auto p = partThree->addComponent<PhysicsComponent>(true, Vector2f(10.0f, 10.0f), constPLAYER, (short)(constWALL | constENEMY | constENEMYBULLET | constPICKUP), &partThree);
			p->impulse(Vector2f(impulse));
		}
		{
			auto s = partFour->addComponent<SpriteComponent>();
			s->setSprite<Sprite>(spriteFour);
			s->getSprite().setScale(0.4, 0.4);
			s->getSprite().setOrigin(100, 100);
			s->getSprite().setTextureRect(IntRect(600, 0, 200, 200));
			s->getSprite().setRotation(playerSprite->getSprite().getRotation());
			partFour->addTag("part");

			Vector2f impulse = sf::rotate(Vector2f(0, 5.f), playerSprite->getSprite().getRotation());
			impulse = Vector2f(impulse.x * 0.1, 0);
			auto p = partFour->addComponent<PhysicsComponent>(true, Vector2f(10.0f, 10.0f), constPLAYER, (short)(constWALL | constENEMY | constENEMYBULLET | constPICKUP), &partFour);
			p->impulse(Vector2f(impulse));

		}
		{
			auto s = partFive->addComponent<SpriteComponent>();
			s->setSprite<Sprite>(spriteFive);
			s->getSprite().setScale(0.4, 0.4);
			s->getSprite().setOrigin(100, 100);
			s->getSprite().setTextureRect(IntRect(800, 0, 200, 200));
			s->getSprite().setRotation(playerSprite->getSprite().getRotation());
			partFive->addTag("part");

			Vector2f impulse = sf::rotate(Vector2f(0, 5.f), playerSprite->getSprite().getRotation());
			impulse = Vector2f(impulse.x * 0.1, impulse.y * 0.1);
			auto p = partFive->addComponent<PhysicsComponent>(true, Vector2f(10.0f, 10.0f), constPLAYER, (short)(constWALL | constENEMY | constENEMYBULLET | constPICKUP), &partFive);
			p->impulse(Vector2f(impulse));
		}

		cout << "dead player spawned" << endl;
		player->setForDelete();
		playerDeadSpawned = true;
	}
}


