#pragma once
#include <SFML/Graphics.hpp>

// A single pipe obstacle = one rectangle above the gap, one below.
// Moves left at a constant speed. Owns no game logic beyond its own motion.
class Pipe {
public:
    Pipe(float x, float gapCenterY, float gapSize, float windowHeight);

    void update(float dt, float speed);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getTopBounds() const;
    sf::FloatRect getBottomBounds() const;
    float getX() const;
    bool isOffscreen() const;

    // Used by PipeManager to award points exactly once per pipe.
    bool scored = false;

    static constexpr float WIDTH = 70.f;

private:
    sf::RectangleShape m_top;
    sf::RectangleShape m_bottom;
};
