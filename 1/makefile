#Name: Cody Gonsowski & Ethan Seiber
#File: makefile
#Desc: makefile for assignment #1

CC=gcc

DEBUG=-g

TARGET=shell

CFLAGS=-c -Wall $(DEBUG)

all: $(TARGET)

$(TARGET): shell.o Queue.o
	$(CC) -o $(TARGET) shell.o Queue.o

shell.o: shell.c Queue.h GlobalVars.txt
	$(CC) $(CFLAGS) shell.c

Queue.o: Queue.c Queue.h GlobalVars.txt
	$(CC) $(CFLAGS) Queue.c
clean:
	rm *.o *~ $(TARGET)
