#include "cmp_menu.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "cmp_text.h"
#include <engine.cpp>
#include "../game.h"
using namespace std;
using namespace sf;
// Constructor
Texture textureMenu;
Sprite spriteMenu;

MenuItemComponent::MenuItemComponent(Entity* p, std::string Text) : Component(p)
{

    auto s = _parent->addComponent<SpriteComponent>();
    if (textureMenu.loadFromFile("res/menu-item.png")) {
        spriteMenu.setTexture(textureMenu);
        s->setSprite<Sprite>(spriteMenu);
        s->getSprite().setOrigin(200, 50);

        auto txt = _parent->addComponent<TextComponent>(Text);
        
        txt->SetPosition({_parent->getPosition().x - 150,_parent->getPosition().y - 30});
        txt->SetSize(40);
    }

}

void MenuItemComponent::update(double dt) {
    auto mouse_pos = Mouse::getPosition(Engine::GetWindow());
    float parentX = _parent->getPosition().x;
    float parentY = _parent->getPosition().y;

    if ((mouse_pos.x > parentX - 200) && (mouse_pos.x < parentX + 200) && (mouse_pos.y > parentY - 50) && (mouse_pos.y < parentY + 50)) {
        auto text = _parent->get_components<TextComponent>()[0];
        auto sprite = _parent->get_components<SpriteComponent>()[0];
        text->SetColour(sf::Color::Black);
        sprite->getSprite().setColor(sf::Color::Yellow);

        if (sf::Mouse::isButtonPressed(Mouse::Left)) {
            resolveClick();
        }
    }
    else {
        auto text = _parent->get_components<TextComponent>()[0];
        text->SetColour(sf::Color::White);
        auto sprite = _parent->get_components<SpriteComponent>()[0];
        sprite->getSprite().setColor(sf::Color::White);
    }

}

void MenuItemComponent::resolveClick() {
    auto tagSet = _parent->getTags();
    string parentTag = tagSet.begin()->c_str();

    cout << parentTag << "Clicked" << endl;

    if (parentTag == "start") {
        Engine::ChangeScene(&scene_main);
    }
    else if (parentTag == "exit") {
        exit(EXIT_FAILURE);
    }
    else if (parentTag == "options") {
        Engine::ChangeScene(&scene_settings);
    }
    else if (parentTag == "highscore") {
        Engine::ChangeScene(&scene_highscores);
    }

}

void MenuItemComponent::render()
{
}