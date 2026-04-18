CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = src/main.cpp src/Process.cpp
OUT = process_test

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)