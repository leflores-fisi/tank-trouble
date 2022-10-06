#pragma once
#include <SFML/Graphics.hpp>

class Input {
    inline static std::pair<sf::Keyboard::Key, bool> keysMap[sf::Keyboard::KeyCount] = {};
    inline static std::pair<sf::Mouse::Button, bool> buttonsMap[sf::Mouse::ButtonCount] = {};
  public:
    Input();
    ~Input();
    static void setup();
    static bool isKeyPressed(sf::Keyboard::Key key);
    static bool isButtonPressed(sf::Mouse::Button button);
    static void pushKeyEvent(sf::Event event);
    static void pushMouseEvent(sf::Event event);
};
