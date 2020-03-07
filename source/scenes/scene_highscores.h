#pragma once

#include "engine.h"

class HighScoreScene : public Scene {
public:
   HighScoreScene() = default;
  ~HighScoreScene() override = default;

  void Load() override;

  void Update(const double& dt) override;
};
