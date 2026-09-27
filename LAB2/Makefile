CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

TARGET = agenda
OBJECTS = ces11_vector.o ces11_pqueue.o tarefa.o main.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
