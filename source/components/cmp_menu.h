#pragma once
#include "ecm.h"
#include <SFML/Graphics.hpp>
#include "../scenes/scene_menu.h"
#include "../scenes/main_scene.h"
#include "../scenes/scene_highscores.h"
#include "../scenes/scene_settings.h"

class MenuItemComponent : public Component {

public:
    MenuItemComponent() = delete;
    explicit MenuItemComponent(Entity* p, std::string Text);

    void update(double dt) override;
    void resolveClick();
    void render() override;
};
