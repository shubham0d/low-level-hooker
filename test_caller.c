#include <linux/init.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <asm/set_memory.h>



static int my_init(void)
{
    static int (*add_num)(int a, int b) = (void*)0;
    printk(KERN_INFO "Resolving address of add_num:)\n");
    add_num = (void*)kallsyms_lookup_name("add_num");
    printk(KERN_INFO "sum of numbers is %ld\n", add_num(2,3));
    return  0;
}

static void my_exit(void)
{
    printk(KERN_INFO "Goodbye world.\n");

    return;
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
