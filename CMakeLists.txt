cmake_minimum_required(VERSION 3.25)
project(rpl-sim)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

##############################################################################
# PROJECT FILES
##############################################################################

set(RPLSIM_FILES src/PhoenixPositionProvider.cpp src/PhoenixPositionProviderUtility.cpp src/Vector3.cpp)

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
#set(BOOST_INCLUDEDIR "./lib/boost_1_82_0/")
find_package(Boost 1.74 REQUIRED COMPONENTS program_options) # Expects environmental variable BOOST_INCLUDEDIR
##############################################################################
# LINK LIBRARIES
##############################################################################

include_directories(src)
link_directories(src)

include_directories(lib/spline)
include_directories(lib/json)
include_directories(lib/optparse)

##############################################################################
# PROGRAM BUILD INFRASTRUCTURE
##############################################################################

add_executable(
	main_exe 
	src/main.cpp
	${RPLSIM_FILES}
)

target_link_libraries(main_exe LINK_PUBLIC Boost::boost Boost::program_options)
target_link_libraries(main_exe PRIVATE Eigen3::Eigen)

##############################################################################
# INCLUDE CSVS WITH BUILD INFRASTRUCTURE
##############################################################################
add_custom_command(
	TARGET main_exe PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/data/atmosisa.csv 
	$<TARGET_FILE_DIR:main_exe>/atmosisa.csv 
)

add_custom_command(
	TARGET main_exe PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/data/mach_vs_cd.csv 
	$<TARGET_FILE_DIR:main_exe>/mach_vs_cd.csv 
)

add_custom_command(
	TARGET main_exe PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/data/thrust_curve.csv 
	$<TARGET_FILE_DIR:main_exe>/thrust_curve.csv 
)

##############################################################################
# TEST INFRASTRUCTURE
##############################################################################

add_executable(
	tests 
	test/tests.cpp
	${RPLSIM_FILES}
)

target_link_libraries(tests LINK_PUBLIC Boost::boost Boost::program_options)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain Eigen3::Eigen)

# https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)
