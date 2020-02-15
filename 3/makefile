
CC=gcc
TARGET=banking

all: $(TARGET)

$(TARGET): banking.o
	$(CC) -pthread -o $(TARGET) banking.o

banking.o: banking.c
	$(CC) -c banking.c

clean:
	rm *.o $(TARGET)
