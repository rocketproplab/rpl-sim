INCLUDES = -Ilib
SRCS = src/sim.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = rplsim

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(INCLUDES) -o $(TARGET) $(OBJS)

.cpp.o:
	g++ $(INCLUDES) -c $< -o $@

clean:
	rm src/*.o *~ $(TARGET)


# .PHONY: all test clean build

# test:
# 	cmake -S . -B build
# 	cmake --build build


# build:
# 	g++ -std=c++14 -Ilib src/sim.cpp src/PhoenixPositionProvider.cpp src/FluidToEngineSubsystem.cpp -o rpl-sim


# clean:
# 	rm -rf build
# 	rm rpl-sim