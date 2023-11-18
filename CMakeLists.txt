cmake_minimum_required(VERSION 3.25)
project(rpl-sim)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)
add_executable(tests test/tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
