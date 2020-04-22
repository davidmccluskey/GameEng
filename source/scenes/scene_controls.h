#pragma once

#include "engine.h"

class ControlsScreen : public Scene {
public:
    ControlsScreen() = default;
  ~ControlsScreen() override = default;

  void Load() override;

  void Update(const double& dt) override;
  void UnLoad();
  void iterate();
};
