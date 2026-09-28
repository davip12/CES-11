CC = gcc
CFLAGS = -Wall -Wextra -pedantic

TARGET = main
OBJECTS = ces11_list.o ces11_ccqueue.o ces11_dlstack.o game.o main.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $? -o $@

clean:
	rm *.o $(TARGET)
