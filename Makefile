build:
	g++ -Isrc/Eigen src/test.cpp -o rpl-sim

clean:
	rm rpl-sim
