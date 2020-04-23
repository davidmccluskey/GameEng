#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_enter_score.h"
#include "scenes/scene_highscores.h"
#include "scenes/scene_settings.h"
#include "score.h"
#include "options.h"
#include <fstream>
using namespace std;

MenuScene menu;
MainScene scene_main;   //Main scene reference
HighScoreScene scene_highscores;    //High score scene reference
SettingsScreen scene_settings; //Settings scene reference
EnterScoreScreen scene_enter_highscore;
ControlsScreen scene_controls;
Score score;
string name;
float clickCooldown = 0;
bool _paused = false;
int _enemyNum = 0;
sf::Music music;

float windowWidth;
float windowHeight;

int main() {
	ifstream inFile;
	inFile.open("options.txt");
	srand(time(0));
	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		//exit(1);   // call system to stop
	}
	std::vector<int> input;
	int item;

	while (inFile >> item) {
		input.push_back(item);
	}
	//string volumeStr = to_string(volume);
	//string windowModeStr = to_string(windowMode);
	//string musicOnStr = to_string(musicOn);
	//string effectsOnStr = to_string(effectsOn);
	//string widthStr = to_string(width);
	//string heightStr = to_string(height);

	Options::instance()->volume = input[0];
	Options::instance()->windowMode = input[1];
	Options::instance()->musicOn = input[2];
	Options::instance()->effectsOn = input[3];

	Options::instance()->width = input[4];
	Options::instance()->height = input[5];
	Options::instance()->launchWidth = input[4];
	Options::instance()->launchHeight = input[5];

	Options::instance()->moveLeft = input[6];
	Options::instance()->moveRight = input[7];
	Options::instance()->shootKey = input[8];
	Options::instance()->pauseKey = input[9];

	inFile.close();

	windowWidth = Options::instance()->launchWidth;
	windowHeight = Options::instance()->launchHeight;
	Engine::Start(Options::instance()->width, Options::instance()->height, "GUN THRUSTERS", &menu, Options::instance()->windowMode);  //Starts engine in user specified resolution
}