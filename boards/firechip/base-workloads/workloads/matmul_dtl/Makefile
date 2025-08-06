CXX := g++
CXXFLAGS := -std=c++17 -O2 -Iagu_dtl/src/
LDFLAGS := -Lagu_dtl -ldtl

# Your source files
SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)
MAIN := main.o
TARGET := myprogram

.PHONY: all clean lib

all: lib $(TARGET)

# Rule to build the final binary
$(TARGET): $(OBJ) $(MAIN)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Rule to compile main.cpp
$(MAIN): main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile source files in src/
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build the static library by entering agu_dtl/
lib:
	$(MAKE) -C agu_dtl/src

clean:
	$(MAKE) -C agu_dtl clean
	rm -f $(OBJ) $(MAIN) $(TARGET)
