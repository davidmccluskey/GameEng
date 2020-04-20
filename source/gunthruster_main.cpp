#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_enter_score.h"
#include "scenes/scene_highscores.h"
#include "scenes/scene_settings.h"
#include "score.h"

using namespace std;

MenuScene menu;
MainScene scene_main;   //Main scene reference
HighScoreScene scene_highscores;    //High score scene reference
SettingsScreen scene_settings; //Settings scene reference
EnterScoreScreen scene_enter_highscore;
Score score;
string name;
float clickCooldown = 0;
bool _paused = false;
int _enemyNum = 0;
sf::Music music;

int main() {
  Engine::Start(gameWidth, gameHeight, "GUN THRUSTERS",&menu);  //Starts engine in user specified resolution
}