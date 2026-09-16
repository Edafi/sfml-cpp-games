#hey: one two
	# Outputs "hey", since this is the target name
#	echo $@

	# Outputs all prerequisites newer than the target
#	echo $?

	# Outputs all prerequisites
#	echo $^

	# Outputs the first prerequisite
#	echo $<

#Compiling a C program: n.o is made automatically from n.c with a command of the form $(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@
#Compiling a C++ program: n.o is made automatically from n.cc or n.cpp with a command of the form $(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
#Linking a single object file: n is made automatically from n.o by running the command $(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

CXX := g++
CC := gcc
CXXFLAGS := -std=c++17 -Wall
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
TARGET := timber.out
SRC := main.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

# Линковка
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Компиляция
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(TARGET)
