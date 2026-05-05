# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Program name
TARGET = demo

# Source file with main()
SRC = demo.cc

# Header and template implementation files
HEADERS = MySet.h setinterface.h MySet.cc

# Default rule
all: $(TARGET)

# Build executable
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Remove compiled files
clean:
	rm -f $(TARGET)