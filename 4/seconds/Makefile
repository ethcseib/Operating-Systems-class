#Author: Ethan Seiber
#Date: Feb. 25, 2020
#File: Makefile
#Description: compiles the C program seconds.c into a module object file.

obj-m += seconds.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
