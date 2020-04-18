#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_highscores.h"
#include "scenes/scene_settings.h"

using namespace std;

MenuScene menu;
MainScene scene_main;   //Main scene reference
HighScoreScene scene_highscores;    //High score scene reference
SettingsScreen scene_settings; //Settings scene reference

sf::Music music;

int main() {
  Engine::Start(gameWidth, gameHeight, "GUN THRUSTERS",&menu);  //Starts engine in user specified resolution
}