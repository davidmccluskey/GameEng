#include "main_scene.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include "../components/cmp_text.h"
#include "../components/cmp_player_movement.h"
#include "../components/cmp_player_fire.h"
#include "../components/cmp_physics.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "system_renderer.h"
using namespace std;
using namespace sf;

static shared_ptr<Entity> player; //Player Entity
sf::Texture spritesheet; //Player spritesheet
sf::Sprite playerSprite; //Player sprite

Texture backgroundtexture;	//Background spritesheet
Sprite backgroundSprite;	//Background sprite

sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f)); //View (camera) reference

void MainScene::Load() {
	//Loads in player spritesheet and background sprite
	if (!spritesheet.loadFromFile("res/SpriteSheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	if (!backgroundtexture.loadFromFile("res/background.jpeg")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	Vector2u size = backgroundtexture.getSize(); //Gets size of background texture
	backgroundSprite.setTexture(backgroundtexture); //Sets  background sprite to background texture

	sf::Vector2u targetSize = Engine::getWindowSize();	//Gets window size to set background sprite (view zooms this in)

	backgroundSprite.setScale(
		(targetSize.x / backgroundSprite.getLocalBounds().width) * 3,
		(targetSize.y / backgroundSprite.getLocalBounds().height) * 3); //Sets background sprite to 3x window size, this allows for a large map and camera
	player = makeEntity();				//create player entity
	player->setPosition({ 400, 400 });	//sets player position to roughly centre screen
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



	//Simulate long loading times UNCOMMENT FOR RELEASE
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//cout << " Main scene Load Done" << endl;


	view.setSize(1200.f, 800.f); //sets size of camera
	view.zoom(1.0f); //sets zoom for camera allowing animation
	view.setCenter(400, 400);
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
}

void MainScene::Render() {
	Renderer::queue(&backgroundSprite);
	Scene::Render();
}
