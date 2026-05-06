CXX = g++

TARGET = group_manager

SOURCES = main.cpp source/Commands.cpp source/Group.cpp source/Student.cpp source/Utilities.cpp

CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude

.PHONY: all test clean

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

test:
	./$(TARGET)

clean:
	rm -f ./$(TARGET)