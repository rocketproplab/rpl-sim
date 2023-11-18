.PHONY: all test clean build

test:
	cmake -S . -B build
	cmake --build build
	cd build && ./tests && cd ..


build:
	g++ -Isrc/Eigen src/test.cpp -o rpl-sim


clean:
	rm -rf build
