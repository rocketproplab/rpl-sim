.PHONY: all test clean build

test:
	cmake -S . -B build
	cmake --build build
	cd build && ./tests && cd ..


build:
	g++ -std=c++14 -Isrc/Eigen -isystem src/boost_1_82_0 src/test.cpp -o rpl-sim


clean:
	rm -rf build
	rm rpl-sim
