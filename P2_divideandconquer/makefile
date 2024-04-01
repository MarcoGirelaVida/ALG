HOME = .
INCLUDE = $(HOME)/include
SRC = $(HOME)/src
BIN = $(HOME)/bin
OBJ = $(HOME)/obj
CFLAGS = -std=c++11 -I$(INCLUDE)

all: main.bin \
	 clean

main.bin: tuercas_tornillos.o
	g++ $(CFLAGS) -o $(BIN)/main.bin $(SRC)/main.cpp $(OBJ)/tuercas_tornillos.o

tuercas_tornillos.o:
	g++ $(CFLAGS) -c -o $(OBJ)/tuercas_tornillos.o $(SRC)/tuercas_tornillos.cpp

clean:
	rm $(OBJ)/tuercas_tornillos.o 