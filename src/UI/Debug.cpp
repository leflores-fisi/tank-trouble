#include <SFML/Graphics.hpp>
#include <iostream>
#include "UI/Debug.hpp"

DebugUI::DebugUI() : fpsCounter(new sf::Text()) {
    if (!this->defaultFont.loadFromFile("static/caskaydiaNF.ttf")) {
        std::cout << "Cant load default font" << std::endl;
    }
    this->fpsCounter->setFont(this->defaultFont);
    this->fpsCounter->setCharacterSize(16);
    this->fpsCounter->setFillColor(sf::Color::White);
}

DebugUI::~DebugUI() {
    delete this->fpsCounter;
}

void DebugUI::update(DebugInfo debugInfo) {
    this->fpsCounter->setString(debugInfo.deltaTime + " fps");
}

void DebugUI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*this->fpsCounter);
}
