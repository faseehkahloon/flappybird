# Flappy Bird (C++ / SFML)

A from-scratch Flappy Bird clone built using **C++17** and the **SFML 2.6.x** graphics library.

## Controls

* **Space** or **Left Click**: flap / start / restart
* **Close the window**: quit the game

## Project Structure

```text
flappybird/
├── CMakeLists.txt
├── include/                 # class headers (.h)
│   ├── Bird.h
│   ├── Pipe.h
│   ├── PipeManager.h
│   └── Game.h
├── src/                     # implementations (.cpp)
│   ├── Bird.cpp
│   ├── Pipe.cpp
│   ├── PipeManager.cpp
│   ├── Game.cpp
│   └── main.cpp
└── assets/
    └── DejaVuSans-Bold.ttf  # used to render the score/menus
```

## How the Code Is Organized

* **Bird** — manages the bird's position and velocity, gravity, flap impulse, drawing, and collision box.
* **Pipe** — represents one obstacle consisting of a top and bottom rectangle, handles movement, and provides its bounds.
* **PipeManager** — manages active pipes, spawns new pipes on a timer, removes off-screen pipes, checks collisions, and tracks the score.
* **Game** — owns the window and main game loop and manages the game state machine: `Menu → Playing → GameOver → restart`.

The project follows an **object-oriented design**, where each class owns its own data and behavior while `Game` coordinates the different components.

## Requirements

* **C++17** compatible compiler
* **CMake 3.16 or newer**
* **SFML 2.6.x**

> **Important:** This project currently uses SFML 2.6.x. SFML 3.x is not supported by the current `CMakeLists.txt`.

## Building

### 1. Install SFML

Install **SFML 2.6.x** on your system.

#### Windows

Download/install SFML 2.6.x and note the location of its CMake package, for example:

```text
C:/path/to/SFML-2.6.2/lib/cmake/SFML
```

When configuring CMake, provide your local SFML path:

```powershell
cmake -S . -B build -G Ninja -DSFML_DIR="C:/path/to/SFML-2.6.2/lib/cmake/SFML"
```

> The SFML path above is only an example. Use the path where SFML is installed on your own computer.

#### Ubuntu/Debian

```bash
sudo apt-get install libsfml-dev cmake g++
```

Make sure the installed SFML version is compatible with the project's required SFML 2.6.x version.

#### macOS

```bash
brew install sfml cmake
```

Make sure the installed SFML version is compatible with SFML 2.6.x.

### 2. Build

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

If CMake cannot automatically find SFML, provide your local SFML installation path using `SFML_DIR`:

```bash
cmake -S . -B build -DSFML_DIR="/path/to/SFML-2.6.2/lib/cmake/SFML"
cmake --build build
```

### 3. Run

Run the executable from the **project root**, because the game loads the font using the relative path:

```text
assets/DejaVuSans-Bold.ttf
```

#### Linux/macOS

```bash
./build/FlappyBird
```

#### Windows

```powershell
.\build\FlappyBird.exe
```

If the font cannot be found, the game can still run, but the score/menu text will not be displayed correctly. A warning will be printed to the console.

## Things Worth Trying Next

These are some possible improvements and good C++ practice:

* Replace the plain shapes with real sprite textures using `sf::Texture` and `sf::Sprite`.
* Add `sf::Sound` effects for flapping, scoring, and collisions.
* Persist the best score to a file instead of resetting it every run.
* Add progressive difficulty by gradually increasing `PIPE_SPEED`.
* Replace the `enum class State` state machine with a proper `State` base class and subclasses as the project grows.
* Add animations and a more polished menu/game-over screen.

## Built With

* **C++17**
* **SFML 2.6.x**
* **CMake**
* **Ninja**
* Object-Oriented Programming (OOP)
