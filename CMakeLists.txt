cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TARGET_H
    src/fluid_engine_sim/FluidToEngineSubsystem.h
)

set(TARGET_SRC
    src/fluid_engine_sim/FluidToEngineSubsystem.cpp
    src/test.cpp
)

add_subdirectory(lib/Catch2)

# These tests can use the Catch2-provided main
add_executable(tests src/fluid_engine_sim/test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
