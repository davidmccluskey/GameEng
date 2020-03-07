#pragma once

#include "engine.h"

class SettingsScreen : public Scene {
public:
   SettingsScreen() = default;
  ~SettingsScreen() override = default;

  void Load() override;

  void Update(const double& dt) override;
};
