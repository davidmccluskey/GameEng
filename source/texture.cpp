#include "texture.h"
#include <fstream>
#include <SFML/Window/Keyboard.hpp>
#include "options.h"
#include <iostream>

using namespace sf;
Textures::Textures(int v) : m_value(v)
{
	if (!playerstates.loadFromFile("res/SpriteSheet.png")) {
		std::cout << "error loading player sprites sheet" << endl;
	}
	if (!asteroid.loadFromFile("res/asteroid_sheet.png")) {
		std::cout << "error loading asteroid sprites sheet" << endl;
	}
	if (!background.loadFromFile("res/background.jpeg")) {
		std::cout << "error loading background" << endl;
	}
	if (!bulletsheet.loadFromFile("res/bulletsheet.png")) {
		std::cout << "error loading player sprites sheet" << endl;
	}
	if (!enemyanimations.loadFromFile("res/enemyanimationsheet.png")) {
		std::cout << "error loading player sprites sheet" << endl;
	}
	if (!pickups.loadFromFile("res/pickups.png")) {
		std::cout << "error loading player sprites sheet" << endl;
	}
	if (!menuitem.loadFromFile("res/menu-item.png")) {
		std::cout << "error loading player sprites sheet" << endl;
	}
	if (!playerdead.loadFromFile("res/playerdead.png")) {
		std::cout << "error loading player sprites sheet" << endl;
	}
}

int Textures::get_value()
{
	return m_value;
}
void Textures::set_value(int v)
{
	m_value = v;
}

Textures* Textures::instance()
{
	if (!s_instance)
		s_instance = new Textures(0);
	return s_instance;
}

Texture& Textures::getAstroid()
{
	return asteroid;
}

Texture& Textures::getBackground()
{
	return background;
}

Texture& Textures::getBulletSheet()
{
	return bulletsheet;
}

Texture& Textures::getEnemyAnimations()
{
	return enemyanimations;
}

Texture& Textures::getPlayerStates()
{
	return playerstates;
}

Texture& Textures::getMenuItem()
{
	return menuitem;
}

Texture& Textures::getPickups()
{
	return pickups;
}

Texture& Textures::getplayerdead()
{
	return playerdead;
}

Textures* Textures::s_instance = 0;


