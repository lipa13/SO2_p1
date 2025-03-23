CXX = g++
CXXFLAGS = -std=c++20 -pthread -Wall -Wextra -O2

SRC = main.cpp
OUT = SO2_p1

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	@del /f $(OUT).exe 2>NUL || rm -f $(OUT)