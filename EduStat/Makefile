CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude
SRC = $(wildcard src/*.cpp)
TARGET = build/student_grades_manager

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p build logs data
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -rf build/* logs/*.log

.PHONY: all run clean
