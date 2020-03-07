#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_highscores.h"
#include "scenes/scene_settings.h"

using namespace std;

MenuScene menu;
MainScene scene_main;
HighScoreScene scene_highscores;
SettingsScreen scene_settings;

int main() {
  Engine::Start(1280, 720, "GUN THRUSTERS",&menu);
}