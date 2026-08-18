#include "PipeManager.h"
#include <algorithm>

PipeManager::PipeManager(float windowWidth, float windowHeight)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight) {
}

void PipeManager::spawnPipe() {
    float maxGapCenter = m_windowHeight - MIN_GAP_CENTER;
    std::uniform_real_distribution<float> dist(MIN_GAP_CENTER, maxGapCenter);
    float gapCenterY = dist(m_rng);

    m_pipes.emplace_back(m_windowWidth, gapCenterY, GAP_SIZE, m_windowHeight);
}

void PipeManager::update(float dt, float speed) {
    m_spawnTimer += dt;
    if (m_spawnTimer >= SPAWN_INTERVAL) {
        m_spawnTimer = 0.f;
        spawnPipe();
    }

    for (auto& pipe : m_pipes) {
        pipe.update(dt, speed);
    }

    // Drop pipes that have scrolled fully off the left edge.
    m_pipes.erase(
        std::remove_if(m_pipes.begin(), m_pipes.end(),
                        [](const Pipe& p) { return p.isOffscreen(); }),
        m_pipes.end());
}

void PipeManager::draw(sf::RenderWindow& window) {
    for (auto& pipe : m_pipes) {
        pipe.draw(window);
    }
}

bool PipeManager::checkCollision(const Bird& bird) const {
    sf::FloatRect birdBounds = bird.getBounds();
    for (const auto& pipe : m_pipes) {
        if (birdBounds.intersects(pipe.getTopBounds()) ||
            birdBounds.intersects(pipe.getBottomBounds())) {
            return true;
        }
    }
    return false;
}

int PipeManager::updateScore(float birdX) {
    for (auto& pipe : m_pipes) {
        if (!pipe.scored && pipe.getX() + Pipe::WIDTH < birdX) {
            pipe.scored = true;
            m_score++;
        }
    }
    return m_score;
}

void PipeManager::reset() {
    m_pipes.clear();
    m_spawnTimer = 0.f;
    m_score = 0;
}
