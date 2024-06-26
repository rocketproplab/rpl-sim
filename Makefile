.PHONY: all test clean build

all: test

build:
	cmake -S . -B build
	cmake --build build

test: build
	cd build && ./tests && cd ..

clean:
	rm -rf build
