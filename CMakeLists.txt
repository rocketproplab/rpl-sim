cmake_minimum_required(VERSION 3.25)
project(rpl-sim)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)


##############################################################################
# CATCH2 AND EIGEN -- REMOTE SOURCE
##############################################################################

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.4.0
)

FetchContent_Declare(
	Eigen3
	GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git"
	GIT_TAG "3.4.0"
)

FetchContent_MakeAvailable(Catch2)
FetchContent_MakeAvailable(Eigen3)

##############################################################################
# BOOST
##############################################################################

# Fetch Boost from included source
# TODO: Possibly use an installed Boost rather than Boost included in the source.
set(BOOST_ENABLE_CMAKE ON)
find_package(Boost 1.82 REQUIRED) # Expects environmental variable BOOST_INCLUDEDIR


##############################################################################

add_executable(
	tests 
	test/tests.cpp
	src/PhoenixPositionProvider.cpp
	src/PhoenixPositionProviderUtility.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain Eigen3::Eigen Boost::boost)
