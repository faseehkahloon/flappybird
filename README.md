# Flappy Bird (C++ / SFML)

A from-scratch Flappy Bird clone using the SFML graphics library.

## Controls
- **Space** or **Left Click**: flap / start / restart
- Close the window to quit

## Project structure
```
flappybird/
├── CMakeLists.txt
├── include/        # class headers (.h)
│   ├── Bird.h
│   ├── Pipe.h
│   ├── PipeManager.h
│   └── Game.h
├── src/            # implementations (.cpp)
│   ├── Bird.cpp
│   ├── Pipe.cpp
│   ├── PipeManager.cpp
│   ├── Game.cpp
│   └── main.cpp
└── assets/
    └── DejaVuSans-Bold.ttf   # used to render the score/menus
```

## How the code is organized
- **Bird** — position/velocity, gravity, flap impulse, its own draw + collision box.
- **Pipe** — one obstacle (top rect + bottom rect), moves left, reports its bounds.
- **PipeManager** — owns all active pipes, spawns new ones on a timer, removes off-screen ones, checks collisions, tracks score.
- **Game** — owns the window and the game loop, runs a simple state machine (`Menu -> Playing -> GameOver -> restart`).

This mirrors the OOP structure you'd use in Java — each class owns its own data and behavior, `Game` just composes them.

## Building

### 1. Install SFML
**Ubuntu/Debian:**
```bash
sudo apt-get install libsfml-dev cmake g++
```
**macOS (Homebrew):**
```bash
brew install sfml cmake
```
**Windows:**
Easiest path is via [vcpkg](https://vcpkg.io):
```powershell
vcpkg install sfml
```
then pass `-DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake` to the cmake command below.

### 2. Build
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### 3. Run
Run it **from the project root** (not from inside `build/`), since the code loads the font using the relative path `assets/DejaVuSans-Bold.ttf`:
```bash
./build/FlappyBird       # Linux/macOS
build\Release\FlappyBird.exe   # Windows
```

If the font can't be found, the game still runs — it just won't draw the score/menu text. You'll see a warning in the console telling you why.

## Things worth trying next (good C++ practice)
- Swap the plain shapes for real sprite textures (`sf::Texture` + `sf::Sprite`).
- Add a `sf::Sound` for flap/score/hit effects.
- Persist the best score to a file instead of resetting it every run.
- Add a `difficulty` that gradually increases `PIPE_SPEED` the longer you survive.
- Replace the `enum class State` machine with a proper `State` base class + subclasses (a common OOP refactor once a project grows).
