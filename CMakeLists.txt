cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TARGET_H
    src/FluidToEngineSubsystem.h
    src/PhoenixPositionProvider.h
)

set(TARGET_SRC
    src/FluidToEngineSubsystem.cpp
    src/PhoenixPositionProvider.cpp
    src/sim.cpp
)

add_subdirectory(lib/Catch2)
add_library(lib/json.hpp)

# These tests can use the Catch2-provided main
add_executable(tests src/sim.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)