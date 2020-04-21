#pragma once
#include "ecm.h"
#include <SFML/Graphics.hpp>

class OptionsItemComponent : public Component {

public:
    OptionsItemComponent() = delete;
    explicit OptionsItemComponent(Entity* p, std::string Text, sf::Vector2f size);

    void update(double dt) override;
	void setSize(float size, float itemSize);
    void setPosition(sf::Vector2f position);
    void render() override;
	void setTextColour(sf::Color color);
    void setBorderColour(sf::Color color);

	void resolveClick();
};
