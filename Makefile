# Top Level Env Variables
export BOOST_INCLUDEDIR := ./src/boost_1_82_0

.PHONY: all test clean build

test:
	cmake -S . -B build -DBOOST_INCLUDEDIR=${BOOST_INCLUDEDIR}
	cmake --build build
	cp src/atmosisa.csv build
	cp src/mach_vs_cd.csv build
	cp src/thrust_curve.csv build
	cd build && ./tests && cd ..


build:
	g++ -std=c++14 -Isrc/Eigen /opt/homebrew/Cellar/boost/1.84.0_1/include src/test.cpp src/PhoenixPositionProvider.cpp src/PhoenixPositionProviderUtility.cpp -o rpl-sim


clean:
	rm -rf build
	rm rpl-sim

# .PHONY: all test clean build

# CC := g++
# CFLAGS := -std=c++14 -Isrc/Eigen -Isrc/boost_1_82_0

# SRCS := src/main.cpp src/PhoenixPositionProvider.cpp src/PhoenixPositionProviderUtility.cpp
# OBJS := $(SRCS:.cpp=.o)

# all: build

# test:
# 	cmake -S . -B build
# 	cmake --build build
# 	cd build && ./tests && cd ..

# build: $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o rpl-sim

# %.o: %.cpp
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -rf build
# 	rm -f rpl-sim
# 	rm -f $(OBJS)
