#include "options.h"
#include <fstream>
#include <SFML/Window/Keyboard.hpp>

using namespace sf;
Options::Options(int v) : m_value(v)
{
	volume = 50;
	windowMode = 0;
	musicOn = 1;
	effectsOn = 1;
	width = 1280;
	height = 720;
	launchWidth = 1280;
	launchHeight = 720;
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




string Options::SFKeytoChar(int keycode) {
	string resturnString;
	switch (keycode) {
	case Keyboard::Escape:
		resturnString = "Esc";
		break;
	case Keyboard::LControl:
		resturnString = "LCTRL";
		break;
	case Keyboard::LShift:
		resturnString = "LSHIFT";
		break;
	case Keyboard::Left:
		resturnString = "<";
		break;
	case Keyboard::Right:
		resturnString = ">";
		break;
	case Keyboard::Up:
		resturnString = "^";
		break;
	case Keyboard::Down:
		resturnString = "DN";
		break;

	case Keyboard::A:
		resturnString = "A";
		break;
	case Keyboard::B:
		resturnString = "B";
		break;
	case Keyboard::C:
		resturnString = "C";
		break;
	case Keyboard::D:
		resturnString = "D";
		break;
	case Keyboard::E:
		resturnString = "E";
		break;
	case Keyboard::F:
		resturnString = "F";
		break;
	case Keyboard::G:
		resturnString = "G";
		break;
	case Keyboard::H:
		resturnString = "H";
		break;
	case Keyboard::I:
		resturnString = "I";
		break;
	case Keyboard::J:
		resturnString = "J";
		break;
	case Keyboard::K:
		resturnString = "K";
		break;
	case Keyboard::L:
		resturnString = "L";
		break;
	case Keyboard::M:
		resturnString = "M";
		break;
	case Keyboard::N:
		resturnString = "N";
		break;
	case Keyboard::O:
		resturnString = "O";
		break;
	case Keyboard::P:
		resturnString = "P";
		break;
	case Keyboard::Q:
		resturnString = "Q";
		break;
	case Keyboard::R:
		resturnString = "R";
		break;
	case Keyboard::S:
		resturnString = "S";
		break;
	case Keyboard::T:
		resturnString = "T";
		break;
	case Keyboard::U:
		resturnString = "U";
		break;
	case Keyboard::V:
		resturnString = "V";
		break;
	case Keyboard::W:
		resturnString = "W";
		break;
	case Keyboard::X:
		resturnString = "X";
		break;
	case Keyboard::Y:
		resturnString = "Y";
		break;
	case Keyboard::Z:
		resturnString = "Z";
		break;

	default:
		resturnString = to_string(keycode);
		break;
	}

	return resturnString;
}

