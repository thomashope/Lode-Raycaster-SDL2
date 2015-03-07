
CC=c++
CFLAGS=-c 
LFLAGS=-framework SDL2 -framework SDL2_image
FLAGS= $(CFLAGS) $(LFLAGS)
SRC=source/
BUILD=build/
OBJECTS= $(BUILD)main.o

# compile and link the whole project
all: build link

# compile only
build: main.o

# link objects
link:
	$(CC) $(OBJECTS) $(LFLAGS) -o rayCaster.o

clean: 
	rm -rf *.o

# compile individual files
main.o: $(SRC)main.cpp
	$(CC) $(CFLAGS) $(SRC)main.cpp -o $(BUILD)main.o

