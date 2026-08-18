#include "Bird.h"
#include <algorithm>

Bird::Bird(float startX, float startY) {
    m_shape.setRadius(RADIUS);
    m_shape.setOrigin(RADIUS, RADIUS); // rotate/position around center
    m_shape.setFillColor(sf::Color(255, 214, 10));   // yellow body
    m_shape.setOutlineColor(sf::Color(200, 140, 0));
    m_shape.setOutlineThickness(2.f);
    m_shape.setPosition(startX, startY);
    m_velocity = {0.f, 0.f};
}

void Bird::flap() {
    m_velocity.y = FLAP_VELOCITY;
}

void Bird::update(float dt) {
    m_velocity.y += GRAVITY * dt;
    m_shape.move(0.f, m_velocity.y * dt);

    // Rotate the bird to reflect vertical speed (dive/climb) - purely cosmetic.
    float rotation = std::clamp(m_velocity.y / 10.f, -25.f, 90.f);
    m_shape.setRotation(rotation);
}

void Bird::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

void Bird::reset(float startX, float startY) {
    m_shape.setPosition(startX, startY);
    m_shape.setRotation(0.f);
    m_velocity = {0.f, 0.f};
}

sf::FloatRect Bird::getBounds() const {
    return m_shape.getGlobalBounds();
}

float Bird::getRotationDegrees() const {
    return m_shape.getRotation();
}
