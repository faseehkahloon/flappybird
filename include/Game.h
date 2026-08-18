#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "PipeManager.h"

// Owns the window and the game loop. Drives a simple state machine:
// Menu -> Playing -> GameOver -> (restart) -> Playing ...
class Game {
public:
    Game();
    void run(); // call this once from main()

private:
    enum class State { Menu, Playing, GameOver };

    void processEvents();
    void update(float dt);
    void render();
    void handleFlapInput();
    void restart();

    sf::RenderWindow m_window;
    sf::Font m_font;
    bool m_fontLoaded = false;

    Bird m_bird;
    PipeManager m_pipeManager;
    State m_state = State::Menu;
    int m_score = 0;
    int m_bestScore = 0;

    static constexpr unsigned int WINDOW_WIDTH = 480;
    static constexpr unsigned int WINDOW_HEIGHT = 720;
    static constexpr float PIPE_SPEED = 180.f;
    static constexpr float GROUND_HEIGHT = 60.f;
};
