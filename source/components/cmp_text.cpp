#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "engine.h"
void TextComponent::update(double dt) {}

void TextComponent::render() { Renderer::queue(&_text); }
//TEXT COMPONENT PROVIDED BY GAMES ENGINEERING PRACTICALS
TextComponent::TextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
  _text.setString(_string);
  _font = Resources::get<sf::Font>("RobotoMono.ttf");
  _text.setFont(*_font);
}

void TextComponent::SetText(const std::string& str) {
  _string = str;
  _text.setString(_string);
}

void TextComponent::SetPosition(sf::Vector2f coords) {
    _text.setPosition(coords);
}
