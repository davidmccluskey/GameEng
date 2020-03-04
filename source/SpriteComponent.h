#pragma once
#include "ecm.h"
#include <SFML/Graphics.hpp>

class SpriteComponent : public Component {
protected:
    std::shared_ptr<sf::Sprite> _sprite;
public:
    SpriteComponent() = delete;
    explicit SpriteComponent(Entity* p);
    void rotateSprite(double dt);
    void update(double dt) override;
    void render() override;

    sf::Sprite& getSprite() const;

    template <typename T, typename... Targs>
    void setSprite(Targs... params) {
        _sprite.reset(new T(params...));
    }
};