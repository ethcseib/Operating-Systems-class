//#include <asm/param.h>//may not be needed.
#include <linux/jiffies.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/module.h>
#include <asm/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "jiffies"

ssize_t proc_read(struct file*, char*, size_t, loff_t*);

static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

int jiffies_init(void){

    proc_create(PROC_NAME, 0, NULL, &proc_ops);    
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);

    return 0;
}

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
