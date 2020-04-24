#pragma once

#include "engine.h"

class MainScene : public Scene {
private:
    float _wavetimer;
    int _wavenumber;
    float _keyboardCooldown = 0;
public:
    void Load() override;

    void UnLoad() override;

    void Update(const double& dt) override;

  void Render() override;

  void createEnemyOrb();

  void createEnemyHarpoon();

  void createEnemySpike();

  void createEnemySmall();

  void reset();
};
