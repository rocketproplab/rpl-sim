.PHONY: all test clean build

test:
	cmake -S . -B build
	cmake --build build
	cp src/atmosisa.csv build
	cp src/mach_vs_cd.csv build
	cp src/thrust_curve.csv build
	cd build && ./tests && cd ..

clean:
	rm -rf build
	rmdir build
