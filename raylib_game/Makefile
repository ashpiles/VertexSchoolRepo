# Define the list of object files
objects = lib/tile_grid.o

# Compiler and flags
CXX = g++
CXXFLAGS = -Ietc/
LDFLAGS = -lopengl32 -lgdi32 -lwinmm

# Build the main executable
game.exe: src/main.cpp $(objects)
	$(CXX) -o game.exe src/main.cpp lib/*.o $(CXXFLAGS) $(LDFLAGS)

# Compile source files into object files (using a pattern rule)
lib/%.o: src/%.cpp src/%.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean up the build files
clean:
	rm -f $(objects) game.exe
