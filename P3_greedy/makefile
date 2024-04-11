HOME = .
INCLUDE = $(HOME)/include
SRC = $(HOME)/src
BIN = $(HOME)/bin
OBJ = $(HOME)/obj
CFLAGS = -std=c++11 -I$(INCLUDE)

all: main.bin \
	 clean

main.bin: red_conexiones.o
	g++ $(CFLAGS) -o $(BIN)/main.bin $(SRC)/main.cpp $(OBJ)/red_conexiones.o

red_conexiones.o:
	g++ $(CFLAGS) -c -o $(OBJ)/red_conexiones.o $(SRC)/red_conexiones.cpp

clean:
	rm $(OBJ)/red_conexiones.o 