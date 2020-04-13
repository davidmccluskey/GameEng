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

class ShapeComponent : public Component {
protected:
    std::shared_ptr<sf::Shape> _shape;
    // sf::Shape _shape;

public:
    ShapeComponent() = delete;

    explicit ShapeComponent(Entity* p);

    void update(double dt) override;
    void render() override;
    sf::Shape& getShape() const;
    template <typename T, typename... Targs> void setShape(Targs... params) {
        _shape.reset(new T(params...));
    }
};