#pragma once
#include "ecm.h"
#include <SFML/Graphics.hpp>

class ControlRemapComponent : public Component {

public:
    ControlRemapComponent() = delete;
    explicit ControlRemapComponent(Entity* p, std::string Text, sf::Vector2f size);

    void update(double dt) override;
	void setSize(float size, float itemSize);
    void setPosition(sf::Vector2f position);
    void render() override;
	void setTextColour(sf::Color color);
    void setBorderColour(sf::Color color);

    void setText(std::string inputText);

    void resolveClick();
	void updateOption(int key);
};
