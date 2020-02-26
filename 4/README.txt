Author: Ethan Seiber
Date: Feb. 25, 2020
File: README.txt
Description: A somewhat exhaustive description of the project.

Files:
	jiff.c/Makefile - jiff.c is a kernel module that will tell the 
		user the number of jiffies there are. Makefile is used
		to make jiff.c compilation and cleanup easy.

	seconds.c/Makefile - seconds.c is also a kernel module that 
		will tell the user the number of seconds that have 
		elapsed since this module was loaded into the 
		system. Makefile makes compilation of seconds.c
		and cleanup easier.

User Manual: 
	1) Compile the .c file using the appropriate Makefile using the 
		keyword make.
	2) Use the command sudo insmod <module>.ko to load the module
		you plan to use into the system.
	3) To execute the commands in the module use cat /proc/jiffies or 
		cat /proc/seconds.
	4) To unload the modules use the command sudo rmmod jiff or 
		sudo rmmod seconds.

Accomplished Features:
	I have both modules up and running meaning the cat /proc/jiffies
	command will return the current number of jiffies and the 
	command cat /proc/seconds returns the number of seconds that have
	elapsed since the module was loaded into the system.

Lingering concerns:
	There is still some code provided in the examples that I do not 
	fully understand its purpose. I did learn how to make useful 
	tools that might prove useful later on if I can find a reason
	to create the tool. 
 
