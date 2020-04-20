#pragma once
#include "ecm.h"
class PickupComponent : public Component {
private:
    float _timer = 10;
    float _flickerTimer = 0.1;
    bool _flicker = true;
public:
    PickupComponent() = delete;
    explicit PickupComponent(Entity* p);

    void update(double dt) override;
    void render() override;
};