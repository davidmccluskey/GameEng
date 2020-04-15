
#pragma once

#include "scenes/main_scene.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_highscores.h"
#include "scenes/scene_settings.h"

extern MenuScene menu;
extern MainScene scene_main;
extern HighScoreScene scene_highscores;
extern SettingsScreen scene_settings;

constexpr uint16_t gameWidth = 1280;
constexpr uint16_t gameHeight = 720;
constexpr uint16_t scale = 3;

const short constWALL = 1;
const short constPLAYER = 2;
const short constBULLET = 4;
const short constENEMY = 8;