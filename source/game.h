
#pragma once

#include "scenes/main_scene.h"
#include "scenes/scene_enter_score.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_highscores.h"
#include "scenes/scene_settings.h"
#include <SFML\Audio\Music.hpp>
#include "score.h"
extern MenuScene menu;
extern MainScene scene_main;
extern HighScoreScene scene_highscores;
extern SettingsScreen scene_settings;
extern EnterScoreScreen scene_enter_highscore;

extern Score score;

extern sf::Music music;

extern bool _paused;

constexpr uint16_t gameWidth = 1280;
constexpr uint16_t gameHeight = 720;
constexpr uint16_t scale = 3;

const short constWALL = 1;
const short constPLAYER = 2;
const short constBULLET = 4;
const short constENEMY = 8;
const short constPICKUP = 16;