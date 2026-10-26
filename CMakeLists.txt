cmake_minimum_required(VERSION 3.20)
project(IntergalaktycznyUber)

# Wymuszenie C++17 (niezbędne do skompilowania pathfinding.cpp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dodanie wszystkich plików źródłowych (.cpp) do pliku wykonywalnego
add_executable(IntergalaktycznyUber
        main.cpp
        mapa.cpp
        pathfinding.cpp
        render.cpp
)