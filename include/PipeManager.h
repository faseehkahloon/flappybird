#pragma once
#include <vector>
#include <random>
#include "Pipe.h"
#include "Bird.h"

// Owns the full set of active pipes: spawns them on a timer,
// advances them, removes ones that scrolled off, and checks collisions.
class PipeManager {
public:
    PipeManager(float windowWidth, float windowHeight);

    void update(float dt, float speed);
    void draw(sf::RenderWindow& window);
    void reset();

    // Returns true if the bird overlaps any pipe (top or bottom half).
    bool checkCollision(const Bird& bird) const;

    // Increments and returns the running score whenever the bird
    // passes a pipe's center for the first time.
    int updateScore(float birdX);

private:
    void spawnPipe();

    std::vector<Pipe> m_pipes;
    float m_windowWidth;
    float m_windowHeight;
    float m_spawnTimer = 0.f;
    int m_score = 0;

    std::mt19937 m_rng{std::random_device{}()};

    static constexpr float SPAWN_INTERVAL = 1.6f;   // seconds between pipes
    static constexpr float GAP_SIZE = 160.f;        // vertical gap the bird flies through
    static constexpr float MIN_GAP_CENTER = 120.f;  // keep gaps away from screen edges
};
