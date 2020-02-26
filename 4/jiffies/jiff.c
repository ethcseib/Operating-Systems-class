/**
 *Author: Ethan Seiber
 *Date: Feb. 25, 2020
 *File: jiff.c
 *Description: Prints the current value for jiffies when the command cat /proc/jiffies is executed.
 */
#include <linux/jiffies.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "jiffies"

/**
 *Function: proc_read
 *Description: This function prints the jiffy number to the user after they execute the command
 *cat /proc/jiffies.
 */
ssize_t proc_read(struct file*, char*, size_t, loff_t*);

/**
 *Struct: file_operations
 *Description: Holds information about the procedure to be executed
 * and the module name.
 */
static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

/**
 *Function: jiffies_init
 *Description: The entry point for the module.
 */
int jiffies_init(void){

    proc_create(PROC_NAME, 0, NULL, &proc_ops);    
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);

    return 0;
}

/**
 *Function: jiffies_exit
 *Description: The exit point for the module.
 */
void jiffies_exit(void){
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

ssize_t proc_read(struct file* file, char* usr_buf, size_t count, loff_t* pos){
    char buffer[BUFFER_SIZE];
    int rv = 0;
    static int completed = 0;
    
    if(completed){
        completed = 0; 
        return 0;
    }

    completed = 1;

    rv = sprintf(buffer, "The jiffies are %lu\n", jiffies);
    copy_to_user(usr_buf, buffer, rv);
    return rv;
}

module_init(jiffies_init);
module_exit(jiffies_exit);
