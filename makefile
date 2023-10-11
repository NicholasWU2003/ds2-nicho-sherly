# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Object files
OBJS = main.o helperfunctie.o

# Executable name
TARGET = CA

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc helperfunctie.h
	$(CXX) $(CXXFLAGS) -c main.cc

helperfunctie.o: helperfunctie.cc helperfunctie.h
	$(CXX) $(CXXFLAGS) -c helperfunctie.cc

clean:
	rm -f $(OBJS) $(TARGET)
