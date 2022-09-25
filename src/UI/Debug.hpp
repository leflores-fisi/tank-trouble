#pragma once
#include <string>

class DebugUI : public sf::Drawable {
    sf::Text *fpsCounter;
    sf::Font defaultFont;

  public:
    struct DebugInfo {
        std::string deltaTime;
    };
    DebugUI();
    ~DebugUI();
    void update(DebugInfo debugInfo);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
