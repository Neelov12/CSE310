CXX = g++
CXXFLAGS = -std=c++11

# List of source files
SRCS = main.cpp data.cpp heap.cpp query.cpp

# List of header files
HDRS = heap.h query.h

# List of object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXE = dijkstra

# Default target
all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS)

# Dependencies
main.o: main.cpp heap.h query.h
data.o: data.cpp 
heap.o: heap.cpp heap.h
query.o: query.cpp query.h

# Clean command
clean:
	rm -f $(OBJS) $(EXE)