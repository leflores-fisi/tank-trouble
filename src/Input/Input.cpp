#include <iostream>
#include "Input/Input.hpp"

tt::Input::Input()  { }
tt::Input::~Input() { }

/*
 * Populate the Input::keysMap and Input::buttonsMap arrays
 * with the sfml key and button codes
 */
void tt::Input::setup(sf::RenderWindow &window) {

    window.setKeyRepeatEnabled(false);
    // Keyboard keys setup
    sf::Keyboard::Key key = sf::Keyboard::Key::A;
    // Iterate and initialize all keys
    while (key != sf::Keyboard::KeyCount) {
        Input::keysMap[key] = std::make_pair(key, false);
        key = sf::Keyboard::Key(key + 1);
    }

    // Mouse buttons setup
    sf::Mouse::Button button = sf::Mouse::Button::Left;
    // Iterate and initialize all mouse buttons
    while (button != sf::Mouse::ButtonCount) {
        Input::buttonsMap[button] = std::make_pair(button, false);
        button = sf::Mouse::Button(button + 1);
    }
}

void tt::Input::pushKeyEvent(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        Input::keysMap[event.key.code].second = true;
    }
    if (event.type == sf::Event::KeyReleased) {
        Input::keysMap[event.key.code].second = false;
    }
}

void tt::Input::pushMouseEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        Input::buttonsMap[event.mouseButton.button].second = true;
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        Input::buttonsMap[event.mouseButton.button].second = false;
    }
}

bool tt::Input::isKeyPressed(sf::Keyboard::Key key) {
    return Input::keysMap[key].second;
}
bool tt::Input::isButtonPressed(sf::Mouse::Button button) {
    return Input::buttonsMap[button].second;
}
