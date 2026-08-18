#include "Game.h"
#include <iostream>
#include <algorithm>

Game::Game()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird - C++/SFML"),
      m_bird(WINDOW_WIDTH / 4.f, WINDOW_HEIGHT / 2.f),
      m_pipeManager(WINDOW_WIDTH, WINDOW_HEIGHT - GROUND_HEIGHT) {
    m_window.setFramerateLimit(60);

    // Font is optional cosmetic polish: if it fails to load (e.g. the
    // assets folder wasn't shipped alongside the exe) the game still
    // runs fine, it just won't show text on screen.
    m_fontLoaded = m_font.loadFromFile("assets/DejaVuSans-Bold.ttf");
    if (!m_fontLoaded) {
        std::cerr << "Warning: could not load assets/DejaVuSans-Bold.ttf "
                  << "(run the exe from the project root). Text will be skipped.\n";
    }
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        float dt = clock.restart().asSeconds();
        // Clamp dt so a debugger pause / lag spike can't cause a huge physics jump.
        if (dt > 0.1f) dt = 0.1f;

        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }

        bool flapKey = (event.type == sf::Event::KeyPressed &&
                        event.key.code == sf::Keyboard::Space);
        bool flapClick = (event.type == sf::Event::MouseButtonPressed &&
                           event.mouseButton.button == sf::Mouse::Left);

        if (flapKey || flapClick) {
            handleFlapInput();
        }
    }
}

void Game::handleFlapInput() {
    switch (m_state) {
        case State::Menu:
            m_state = State::Playing;
            m_bird.flap();
            break;
        case State::Playing:
            m_bird.flap();
            break;
        case State::GameOver:
            restart();
            break;
    }
}

void Game::update(float dt) {
    if (m_state != State::Playing) {
        return; // no physics/pipe movement on menu or game-over screens
    }

    m_bird.update(dt);
    m_pipeManager.update(dt, PIPE_SPEED);
    m_score = m_pipeManager.updateScore(m_bird.getBounds().left);

    float groundY = WINDOW_HEIGHT - GROUND_HEIGHT;
    sf::FloatRect birdBounds = m_bird.getBounds();

    bool hitGround = birdBounds.top + birdBounds.height >= groundY;
    bool hitCeiling = birdBounds.top <= 0.f;
    bool hitPipe = m_pipeManager.checkCollision(m_bird);

    if (hitGround || hitCeiling || hitPipe) {
        m_state = State::GameOver;
        m_bestScore = std::max(m_bestScore, m_score);
    }
}

void Game::restart() {
    m_bird.reset(WINDOW_WIDTH / 4.f, WINDOW_HEIGHT / 2.f);
    m_pipeManager.reset();
    m_score = 0;
    m_state = State::Playing;
}

void Game::render() {
    m_window.clear(sf::Color(78, 192, 202)); // sky blue

    m_pipeManager.draw(m_window);
    m_bird.draw(m_window);

    // Ground strip
    sf::RectangleShape ground({(float)WINDOW_WIDTH, GROUND_HEIGHT});
    ground.setPosition(0.f, WINDOW_HEIGHT - GROUND_HEIGHT);
    ground.setFillColor(sf::Color(222, 184, 96));
    m_window.draw(ground);

    if (m_fontLoaded) {
        sf::Text scoreText(std::to_string(m_score), m_font, 40);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setOutlineColor(sf::Color::Black);
        scoreText.setOutlineThickness(2.f);
        scoreText.setPosition(WINDOW_WIDTH / 2.f - 15.f, 30.f);
        m_window.draw(scoreText);

        if (m_state == State::Menu) {
            sf::Text msg("Press SPACE or Click\nto start", m_font, 22);
            msg.setFillColor(sf::Color::White);
            msg.setOutlineColor(sf::Color::Black);
            msg.setOutlineThickness(2.f);
            sf::FloatRect b = msg.getLocalBounds();
            msg.setPosition(WINDOW_WIDTH / 2.f - b.width / 2.f, WINDOW_HEIGHT / 2.f - 60.f);
            m_window.draw(msg);
        } else if (m_state == State::GameOver) {
            sf::Text msg("Game Over", m_font, 36);
            msg.setFillColor(sf::Color::White);
            msg.setOutlineColor(sf::Color::Black);
            msg.setOutlineThickness(2.f);
            sf::FloatRect b = msg.getLocalBounds();
            msg.setPosition(WINDOW_WIDTH / 2.f - b.width / 2.f, WINDOW_HEIGHT / 2.f - 100.f);
            m_window.draw(msg);

            sf::Text best("Best: " + std::to_string(m_bestScore) +
                           "\nPress SPACE or Click\nto restart", m_font, 20);
            best.setFillColor(sf::Color::White);
            best.setOutlineColor(sf::Color::Black);
            best.setOutlineThickness(2.f);
            sf::FloatRect bb = best.getLocalBounds();
            best.setPosition(WINDOW_WIDTH / 2.f - bb.width / 2.f, WINDOW_HEIGHT / 2.f - 40.f);
            m_window.draw(best);
        }
    }

    m_window.display();
}
