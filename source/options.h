#pragma once
#include <string>
using namespace std;

class Options {
public:
	int m_value;
	static Options* s_instance;
	Options(int v);
public:
	int get_value();
	void set_value(int v);
	static Options* instance();
	void save();
	int volume;
	bool windowMode;
	bool musicOn;
	bool effectsOn;
	int width;
	int height;
};

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object inself.



