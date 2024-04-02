.PHONY: all test clean build

test:
	cmake -S . -B build
	cmake --build build
	cd build && ./tests && cd ..

clean:
	rm -rf build
	rmdir build
