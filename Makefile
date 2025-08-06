# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2 -pthread

# Project files
TARGET = orderbooksim
SRC = main.cpp orderbook.cpp
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files into binary
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean command
clean:
	rm -f $(OBJ) $(TARGET)