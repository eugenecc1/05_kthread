#include<linux/module.h>     
#include<linux/init.h>       
#include<linux/kthread.h>    
#include<linux/sched.h>      
#include<linux/delay.h>      

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eugene Chesna");
MODULE_DESCRIPTION("Kthread demo");

static struct task_struct *th1;
static struct task_struct *th2;
static int t1 = 1;
static int t2 = 2;


int thread_func(void * ptr)
{
	int i = 0;
	int num = * (int * ) ptr;

	while(!kthread_should_stop()){
		printk("Thread %d is excuted! Counter val: %d\n", num, i++);
		msleep(1000);
	
	}

	printk("Kthread %d finished execution!\n.", num);

	return 0;
}

int mod_init(void)
{
	printk("Kthread Module Loaded\n");
	
	th1 = kthread_run(thread_func, &t1, "thread_1");
	if (th1 != NULL)
		printk("Thread 1 created successfully.\n");
	else
	{
		printk("thread 1 not created.\n");
		return -1;
	}
	
		th2 = kthread_run(thread_func, &t2, "thread_2");
	if (th2 != NULL)
		printk("Thread 2 created successfully.\n");
	else
	{
		printk("thread 2 not created.\n");
		return -1;
	}

	printk("Both threads are running now!\n");
	
	return 0;
}


void mod_exit(void)
{
	if (!IS_ERR(th1))
	{
		kthread_stop(th1);
		th1 = NULL;
	}
	

	if (!IS_ERR(th2))
	{
		kthread_stop(th2);
		th2 = NULL;
	}

	printk("Kthread Module Removed\n");

	return;
}


module_init(mod_init);
module_exit(mod_exit);
