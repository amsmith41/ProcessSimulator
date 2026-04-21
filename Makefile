CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = src/Process.cpp src/Simulation.cpp src/FCFSScheduler.cpp src/Logger.cpp src/PageTable.cpp src/MemoryManager.cpp

MAIN = src/main.cpp
TEST = src/tests/TestSimulation.cpp

OUT_MAIN = main
OUT_TEST = test_sim

all: main

main:
	$(CXX) $(CXXFLAGS) $(SRC) $(MAIN) -o $(OUT_MAIN)

test:
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST) -o $(OUT_TEST)

clean:
	rm -f $(OUT_MAIN) $(OUT_TEST)