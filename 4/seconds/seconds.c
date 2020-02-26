/**
 *Author: Ethan Seiber
 *Date: Feb. 25, 2020
 *File: seconds.c
 *Description: Tells the user the amount of time (in seconds) this module has been loaded 
 *into system.
 */

#define PROC_NAME "seconds"
#define BUFFER_SIZE 128

#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <asm/param.h>

unsigned long start;

/**
 *Function: seconds
 *Description: This function calculates the amount of time (in seconds) this module has been
 *loaded into the system.
 */
ssize_t seconds(struct file*, char*, size_t, loff_t*);

/**
 *Struct: file_operations
 *Description: Holds information about the module such as the function to be executed
 *and the module name.
 */
static struct file_operations proc_ops = {
	.owner = THIS_MODULE, 
	.read = seconds,
};

/**
 *Funciton: seconds_init
 *Description: The entry point for the module.
 */
int seconds_init(void){

	start = jiffies;

	proc_create(PROC_NAME, 0, NULL, &proc_ops);
	printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
	return 0;
}

/**
 *Function: seconds_exit
 *Description: The exit point for the module when it is un-loaded from the system.
 */
void seconds_exit(void){
	remove_proc_entry(PROC_NAME, NULL);
	printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

ssize_t seconds(struct file* file, char* usr_buf, size_t count, loff_t* pos){

	int rv = 0;
	char buffer[BUFFER_SIZE];
	unsigned long end;
	static int completed = 0;

	if(completed){
		completed = 0;
		return 0;
	}
	completed = 1;

	end = (jiffies - start)/100;

	rv = sprintf(buffer, "Elapsed time since module was loaded: %lu seconds\n", end);

	copy_to_user(usr_buf, buffer, rv);

	return rv;
	
}

module_init(seconds_init);
module_exit(seconds_exit);
