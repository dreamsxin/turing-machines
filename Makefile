CC=g++
CFLAGS=-Wall -g -ggdb
SOURCES=main.cpp tm.cpp
OBJECTS=$(SOURCES:.cpp=.o)

main: main.cpp
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(OBJECTS) $(CFLAGS) -o turing_machine
	rm -rf *.o

clean:
	rm -rf $(OBJECTS) turing_machine
