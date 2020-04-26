#include "sounds.h"
#include <fstream>
#include <SFML/Window/Keyboard.hpp>
#include "options.h"

using namespace sf;
Sounds::Sounds(int v) : m_value(v)
{
	if (playerhitbuffer.loadFromFile("res/soundFX/enemyhit.wav"))
	{
		playerhitsound.setBuffer(playerhitbuffer);
	}
	if (enemyhitbuffer.loadFromFile("res/soundFX/playerhit.wav"))
	{
		enemyhitsounds.setBuffer(enemyhitbuffer);
	}
	if (blasterbuffer.loadFromFile("res/soundFX/blaster.wav"))
	{
		blastersound.setBuffer(blasterbuffer);
	}
	if (errorbuffer.loadFromFile("res/soundFX/error.wav"))
	{
		errorsound.setBuffer(errorbuffer);
	}
	if (bossBuffer.loadFromFile("res/soundFX/bossSound.wav"))
	{
		bossSound.setBuffer(bossBuffer);
	}
}

int Sounds::get_value()
{
	return m_value;
}
void Sounds::set_value(int v)
{
	m_value = v;
}

Sounds* Sounds::instance()
{
	if (!s_instance)
		s_instance = new Sounds(0);
	return s_instance;
}
void Sounds::playBlaster()
{
	blastersound.setVolume(Options::instance()->volume / 5);
	blastersound.play();
}
void Sounds::playPlayerHit()
{
	playerhitsound.setVolume(Options::instance()->volume / 3);
	playerhitsound.play();
}
void Sounds::playEnemyHit()
{
	enemyhitsounds.setVolume(Options::instance()->volume / 5);
	enemyhitsounds.play();
}
void Sounds::playError()
{
	errorsound.setVolume(Options::instance()->volume);
	errorsound.play();
}
void Sounds::playBoss()
{
	bossSound.setVolume(Options::instance()->volume);
	bossSound.play();
}
Sounds* Sounds::s_instance = 0;


