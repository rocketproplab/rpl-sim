.PHONY: all test clean build

test:
	cmake -S . -B build
	cmake --build build
	cp src/atmosisa.csv build
	cp src/mach_vs_cd.csv build
	cp src/thrust_curve.csv build
	cd build && ./tests && cd ..


build:
	g++ -std=c++14 -Isrc/Eigen src/boost_1_82_0/include src/test.cpp src/PhoenixPositionProvider.cpp src/PhoenixPositionProviderUtility.cpp -o rpl-sim


clean:
	rm -rf build
	rmdir build
