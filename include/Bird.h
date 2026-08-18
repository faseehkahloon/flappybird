#pragma once
#include <SFML/Graphics.hpp>

// The player-controlled bird.
// Physics-wise this is just a point mass affected by gravity,
// with an instant upward velocity kick when the player flaps.
class Bird {
public:
    Bird(float startX, float startY);

    void flap();                     // called on spacebar / click
    void update(float dt);           // dt = seconds since last frame
    void draw(sf::RenderWindow& window);
    void reset(float startX, float startY);

    sf::FloatRect getBounds() const; // for collision checks
    float getRotationDegrees() const;

private:
    sf::CircleShape m_shape;
    sf::Vector2f m_velocity;

    static constexpr float GRAVITY = 900.f;      // pixels/sec^2
    static constexpr float FLAP_VELOCITY = -320.f; // pixels/sec (negative = up)
    static constexpr float RADIUS = 16.f;
};
