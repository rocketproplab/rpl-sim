#include <catch2/catch_test_macros.hpp>

/****************************************
REMEMBER TO ADD TEST EXECUTABLE TO CMakeLists.txt IF YOU CREATE A NEW CPP FILE FOR TESTS
*****************************************/

TEST_CASE("Hello world test", "[hello]"){
	REQUIRE(1 == 1);
}
