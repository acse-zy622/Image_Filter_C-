# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Executable name
TARGET = image_processing_test

# Source files
SOURCES = main.cpp ImageProcessingTests.cpp Filter.cpp Image.cpp

# Object files
OBJECTS = $(addprefix src/, $(SOURCES:.cpp=.o))

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)

