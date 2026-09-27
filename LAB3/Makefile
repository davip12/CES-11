CC = gcc
CFLAGS = -Wall -Wextra -pedantic

TARGET = main
OBJECTS = main.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $? -o $@

clean:
	rm *.o $(TARGET)
