#pragma once
#include <string>

namespace tt {

class DebugUI : public sf::Drawable {
    sf::Text *fpsCounter;
    sf::Text *entityCounter;
    sf::Font defaultFont;

  public:
    struct DebugInfo {
        std::string fpsCount;
        std::string entityCount;
    };
    DebugUI();
    ~DebugUI();
    void update(DebugInfo debugInfo);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
}
