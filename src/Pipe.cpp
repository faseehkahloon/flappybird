#include "Pipe.h"

Pipe::Pipe(float x, float gapCenterY, float gapSize, float windowHeight) {
    float gapTop = gapCenterY - gapSize / 2.f;
    float gapBottom = gapCenterY + gapSize / 2.f;

    m_top.setSize({WIDTH, gapTop});
    m_top.setPosition(x, 0.f);
    m_top.setFillColor(sf::Color(60, 180, 75));
    m_top.setOutlineColor(sf::Color(30, 110, 40));
    m_top.setOutlineThickness(2.f);

    m_bottom.setSize({WIDTH, windowHeight - gapBottom});
    m_bottom.setPosition(x, gapBottom);
    m_bottom.setFillColor(sf::Color(60, 180, 75));
    m_bottom.setOutlineColor(sf::Color(30, 110, 40));
    m_bottom.setOutlineThickness(2.f);
}

void Pipe::update(float dt, float speed) {
    m_top.move(-speed * dt, 0.f);
    m_bottom.move(-speed * dt, 0.f);
}

void Pipe::draw(sf::RenderWindow& window) {
    window.draw(m_top);
    window.draw(m_bottom);
}

sf::FloatRect Pipe::getTopBounds() const {
    return m_top.getGlobalBounds();
}

sf::FloatRect Pipe::getBottomBounds() const {
    return m_bottom.getGlobalBounds();
}

float Pipe::getX() const {
    return m_top.getPosition().x;
}

bool Pipe::isOffscreen() const {
    return getX() + WIDTH < 0.f;
}
