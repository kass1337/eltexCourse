
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include<linux/sched.h>
#include <linux/init.h> 
#include <linux/slab.h>

int lenf,temp;

char *msg;

ssize_t read_proc(struct file* fil, char __user* buf, size_t len, loff_t* off ) 
{
if(len>temp)
{
len=temp;
}
temp=temp-len;
copy_to_user(buf,msg, len);
if(len==0)
temp=lenf;
   
return len;
}

ssize_t write_proc(struct file* fil, const char __user* buf, size_t len, loff_t* off)
{
copy_from_user(msg,buf,len);
lenf=len;
temp=lenf;
return len;
}

struct proc_ops proc_fops = {
proc_read: read_proc,
proc_write: write_proc
};
void create_new_proc_entry(void)  //use of void for no arguments is compulsory now 
{
proc_create("eltexM5",0,NULL, &proc_fops);
msg=kmalloc(10*sizeof(char), GFP_KERNEL);
}


int proc_init (void) {
 create_new_proc_entry();
 return 0;
}

void proc_cleanup(void) {
 remove_proc_entry("eltexM5",NULL);
 kfree(msg);
}

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Shevlyakov");
MODULE_DESCRIPTION("Hello world");
module_init(proc_init);
module_exit(proc_cleanup);
