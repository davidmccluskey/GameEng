
#pragma once

#include "scenes/main_scene.h"
#include "scenes/scene_enter_score.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_highscores.h"
#include "scenes/scene_settings.h"
#include "scenes/scene_controls.h"
#include <SFML\Audio\Music.hpp>
#include "score.h"
extern MenuScene menu;
extern MainScene scene_main;
extern HighScoreScene scene_highscores;
extern SettingsScreen scene_settings;
extern EnterScoreScreen scene_enter_highscore;
extern ControlsScreen scene_controls;
extern Score score;
extern string name;

extern float clickCooldown;
extern sf::Music music;

extern bool _paused;

extern int _enemyNum;

extern float windowWidth;
extern float windowHeight;

constexpr uint16_t gameWidth = 1280;
constexpr uint16_t gameHeight = 720;
constexpr uint16_t scale = 3;

const short constWALL = 1;
const short constPLAYER = 2;
const short constBULLET = 4;
const short constENEMY = 8;
const short constPICKUP = 16;
const short constENEMYBULLET = 32;