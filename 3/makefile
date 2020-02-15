#Name: Ethan Seiber
#Date: 2/15/2020
#File: makefile
#Description: This is a makefile for compiling the banking.c project file.

CC=gcc
TARGET=banking

all: $(TARGET)

$(TARGET): banking.o
	$(CC) -pthread -o $(TARGET) banking.o

banking.o: banking.c
	$(CC) -c banking.c

clean:
	rm *.o $(TARGET)
