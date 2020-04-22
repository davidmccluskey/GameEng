#include "options.h"
#include <fstream>

Options::Options(int v) : m_value(v)
{
	volume = 50;
	windowMode = 0;
	musicOn = 1;
	effectsOn = 1;
	width = 1280;
	height = 720;

	moveLeft = 0;
	moveRight = 3;
	shootKey = 22;
	pauseKey = 36;
}

int Options::get_value()
{
	return m_value;
}
void Options::set_value(int v)
{
	m_value = v;
}

Options* Options::instance()
{
	if (!s_instance)
		s_instance = new Options(0);
	return s_instance;
}

void Options::save() {
	std::ofstream outfile;
	string volumeStr = to_string(volume);
	string windowModeStr = to_string(windowMode);
	string musicOnStr = to_string(musicOn);
	string effectsOnStr= to_string(effectsOn);
	string widthStr = to_string(width);
	string heightStr = to_string(height);

	string ctrlLeft = to_string(moveLeft);
	string ctrlRight = to_string(moveRight);
	string ctrlShoot = to_string(shootKey);
	string ctrlPause = to_string(pauseKey);

	string output = volumeStr + "\n" + windowModeStr + "\n" + musicOnStr + "\n" + effectsOnStr + "\n" + widthStr + "\n" + heightStr + "\n" + ctrlLeft + "\n" + ctrlRight + "\n" + ctrlShoot + "\n" + ctrlPause;
	std::ofstream ofs("options.txt", std::ofstream::trunc);
	ofs << output;
	ofs.close();
}
Options* Options::s_instance = 0;
