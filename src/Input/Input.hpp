#pragma once
#include <SFML/Graphics.hpp>

namespace tt {

class Input {
    inline static std::pair<sf::Keyboard::Key, bool> keysMap[sf::Keyboard::KeyCount] = {};
    inline static std::pair<sf::Mouse::Button, bool> buttonsMap[sf::Mouse::ButtonCount] = {};
  public:
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;
    static void setup(sf::RenderWindow &window);
    static bool isKeyPressed(sf::Keyboard::Key key);
    static bool isButtonPressed(sf::Mouse::Button button);
    static void pushKeyEvent(sf::Event event);
    static void pushMouseEvent(sf::Event event);
  private:
    ~Input();
};
}
