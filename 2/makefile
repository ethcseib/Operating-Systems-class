#Name: Ethan Seiber
#File: makefile
#Description: A makefile for assignment 2

CC = gcc

TARGET = sudoku

all: $(TARGET)

$(TARGET): sudoku.o
	$(CC) -pthread -o  $(TARGET) sudoku.o

sudoku.o: sudoku.c
	$(CC) -c sudoku.c

clean:
	rm *.o $(TARGET)
