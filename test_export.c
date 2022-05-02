#include <linux/init.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <asm/set_memory.h>




int add_num(int i, int j)
{
    return i+j;
}
EXPORT_SYMBOL(add_num);
static int my_init(void)
{
    printk(KERN_INFO "add_num function is exported:)\n");
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
