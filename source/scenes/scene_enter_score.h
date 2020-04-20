#pragma once

#include "engine.h"

class EnterScoreScreen : public Scene {
public:
    EnterScoreScreen() = default;
    ~EnterScoreScreen() override = default;
    float _keyboardCooldown = 0;

    void Load() override;

    void Update(const double& dt) override;
};
