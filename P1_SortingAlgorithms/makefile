HOME = .
INCLUDE = $(HOME)/include
SRC = $(HOME)/src
BIN = $(HOME)/bin
OBJ = $(HOME)/obj
CFLAGS = -std=c++11 -I$(INCLUDE)

all: main.bin \
	 clean

main.bin: quicksort.o
	g++ $(CFLAGS) -o $(BIN)/main.bin $(SRC)/main.cpp $(OBJ)/quicksort.o

quicksort.o:
	g++ $(CFLAGS) -c -o $(OBJ)/quicksort.o $(SRC)/quicksort.cpp

clean:
	rm $(OBJ)/quicksort.o 