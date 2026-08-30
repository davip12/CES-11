CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -I"../LAB1"

TARGET = pqueue.exe
OBJECTS = ../LAB1/ces11_vector.o ces11_pqueue.o main.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(OBJECTS): %.o: %.c

clean:
	rm -f $(TARGET) $(OBJECTS)
