CC = gcc
CFLAGS = -Wall -Wextra -pedantic

TARGET = exe
OBJECTS = ces11_list.o ces11_ccqueue.o ces11_dlstack.o game.o main.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) *.txt
