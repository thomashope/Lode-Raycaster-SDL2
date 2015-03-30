
CC=g++
CFLAGS=-c
LFLAGS=-framework SDL2
FLAGS= $(CFLAGS) $(LFLAGS)
SRC=source/
BUILD=build/
OBJECTS= $(BUILD)main.o $(BUILD)instantcg.o

# compile and link the whole project
all: build link

# compile only
build: main.o instantcg.o

# link objects
link:
	$(CC) $(OBJECTS) $(LFLAGS) -o rayCaster.out

clean:
	rm -rf *.o *.out

# compile individual files
main.o: $(SRC)main.cpp
	$(CC) $(CFLAGS) $(SRC)main.cpp -o $(BUILD)main.o

# compile InstantCG as an .o file
instantcg.o:
	$(CC) $(CFLAGS) $(SRC)instantcg.cpp -o $(BUILD)instantcg.o
