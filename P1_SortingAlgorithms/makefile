HOME = .
INCLUDE = $(HOME)/include
SRC = $(HOME)/source
BIN = $(HOME)/bin
OBJ = $(OBJ)/obj
CFLAGS = -std=c++11 -I$(include)

all: $(BIN)/main.bin

$(BIN)/main.bin: $(OBJ)/quicksort.o, $(SOURCE)/main.cpp
	g++ $(CFLAGS) -o $(BIN)/main.bin $(SRC)/main.cpp $(OBJ)/quicksort.o

$(OBJ)/quicksort.o: $(INCLUDE)/quicksort.hpp, $(SRC)/quicksort.cpp
	g++ $(CFLAGS) -c $(SRC)/quicksort.cpp

$(BIN)/quicksort.bin: $(INCLUDE)/quicksort.hpp, $(SRC)/quicksort.cpp
	g++ $(CFLAGS) -o $(BIN)/quicksort.bin $(SRC)/quicksort.cpp

clean:
	rm quicksort.bin