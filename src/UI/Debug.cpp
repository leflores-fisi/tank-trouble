#include <SFML/Graphics.hpp>
#include <iostream>
#include "UI/Debug.hpp"

tt::DebugUI::DebugUI() :
    fpsCounter(new sf::Text()),
    entityCounter(new sf::Text()) {

    if (!this->defaultFont.loadFromFile("static/caskaydiaNF.ttf")) {
        std::cout << "Cant load default font" << std::endl;
    }
    this->fpsCounter->setFont(this->defaultFont);
    this->fpsCounter->setCharacterSize(16);
    this->fpsCounter->setFillColor(sf::Color::White);

    this->entityCounter->setFont(this->defaultFont);
    this->entityCounter->setCharacterSize(16);
    this->entityCounter->setFillColor(sf::Color::White);
}

tt::DebugUI::~DebugUI() {
    delete this->fpsCounter;
    delete this->entityCounter;
}

void tt::DebugUI::update(DebugInfo debugInfo) {
    this->fpsCounter->setString(debugInfo.fpsCount + " fps");
    this->entityCounter->setString(debugInfo.entityCount + " entities");
    this->entityCounter->setPosition(0, this->fpsCounter->getGlobalBounds().height + 5.f);
}

void tt::DebugUI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*this->fpsCounter);
    target.draw(*this->entityCounter);
}
