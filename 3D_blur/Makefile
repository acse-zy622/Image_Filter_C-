# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -O3

# Executable name
# TARGET = Volume_3D_medianblur_test
TARGET = Volume_3D_gaussianblur_test

# Source files
# SOURCES = Volume_3D_medianblur.cpp Image.cpp Volume.cpp
SOURCES = Volume_3D_gaussianblur.cpp Image.cpp Volume.cpp

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

