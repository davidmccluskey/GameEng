#pragma once
#include <string>
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include <SFML\Graphics\Texture.hpp>

using namespace std;
using namespace sf;
class Textures {
private:
	int m_value;
	static Textures* s_instance;
	Textures(int v);

	Texture asteroid;
	Texture background;
	Texture bulletsheet;
	Texture enemyanimations;
	Texture playerstates;
	Texture menuitem;
	Texture pickups;
	Texture playerdead;


public:
	int get_value();
	void set_value(int v);
	static Textures* instance();

	Texture& getAstroid();
	Texture& getBackground();
	Texture& getBulletSheet();
	Texture& getEnemyAnimations();
	Texture& getPlayerStates();
	Texture& getMenuItem();
	Texture& getPickups();
	Texture& getplayerdead();

};
