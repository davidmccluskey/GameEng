#pragma once

#include "engine.h"

class CreditsScene : public Scene {
public:
    CreditsScene() = default;
  ~CreditsScene() override = default;

  void Load() override;

  void Update(const double& dt) override;
};
