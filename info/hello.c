/*
 * hello.c - The Hello, World Kernel Module
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/*
 * hello_int - the init function, called when the module is loaded.
 * return zero if successfully loaded, nonzero otherwise.
 */

static int hello_int(void)
{
	printk(KERN_ALERT "I bear a charmed life. \n");
	return 0;
}

/*
 * hello_exit - the exit function is called when the module is removed.
 */

static void hello_exit(void)
{
	printk(KERN_ALERT "Out, out, breif candle!\n");
}

module_init(hello_int);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sekhar Pariga");
MODULE_DESCRIPTION("A Hello, World Module");