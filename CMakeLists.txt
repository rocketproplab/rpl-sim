cmake_minimum_required(VERSION 3.25)
project(rpl-sim)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.4.0
)

set(BOOST_ENABLE_CMAKE ON)

FetchContent_Declare(
  Boost
  URL https://github.com/boostorg/boost/releases/download/boost-1.81.0/boost-1.81.0.tar.xz
  URL_MD5 6cf0cdd797bca685910d527ae3c08cb3
  DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_Declare(
	Eigen3
	GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git"
	GIT_TAG "3.4.0"
)

FetchContent_MakeAvailable(Catch2)
FetchContent_MakeAvailable(Boost)
FetchContent_MakeAvailable(Eigen3)

include_directories(/opt/homebrew/Cellar/boost/1.84.0_1/include)
#link_directories(src/boost_1_82_0/stage/lib)

add_executable(
	tests 
	test/tests.cpp
	src/PhoenixPositionProvider.cpp
	src/PhoenixPositionProviderUtility.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain Eigen3::Eigen)