.PHONY: all test clean build

test:
	cmake -S . -B build
	cmake --build build
	cd build && ./tests && cd ..


build:
	g++ -std=c++14 -Isrc/Eigen -Isrc/boost_1_82_0 src/main.cpp -o rpl-sim


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
