#pragma once
#include <string>
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
using namespace std;
using namespace sf;
class Sounds {
public:
	int m_value;
	static Sounds* s_instance;
	Sounds(int v);
	SoundBuffer blasterbuffer;
	Sound blastersound;

	SoundBuffer playerhitbuffer;
	Sound playerhitsound;

	SoundBuffer enemyhitbuffer;
	Sound enemyhitsounds;
public:
	int get_value();
	void set_value(int v);
	static Sounds* instance();

	void playBlaster();
	void playPlayerHit();
	void playEnemyHit();



};
