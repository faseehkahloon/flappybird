cmake_minimum_required(VERSION 3.16)
project(FlappyBird LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/dev/Libraries/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(FlappyBird
    src/main.cpp
    src/Game.cpp
    src/Bird.cpp
    src/Pipe.cpp
    src/PipeManager.cpp
)

target_include_directories(FlappyBird PRIVATE include)
target_link_libraries(FlappyBird sfml-graphics sfml-window sfml-system)

# Put the executable next to the CMakeLists.txt / assets folder so that
# the relative path "assets/DejaVuSans-Bold.ttf" used in Game.cpp resolves
# correctly when you run it (e.g. ./build/FlappyBird from the project root).
set_target_properties(FlappyBird PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
)
