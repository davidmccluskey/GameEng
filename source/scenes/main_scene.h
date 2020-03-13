#pragma once

#include "engine.h"

class MainScene : public Scene {
private:
    float _wavetimer;
public:
  void Load() override;

  void UnLoad() override;

  void Update(const double& dt) override;

  void Render() override;
};
