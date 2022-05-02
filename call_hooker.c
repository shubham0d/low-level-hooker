#include <linux/init.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <asm/set_memory.h>

//static char *hooker_victim = "add_me";

static int hookers_piston(int a, int b)
{
    return a*b;
}


static int my_init(void)
{

    char *hex_bytes;
    u64 addr;
    u64 addr_new;
    unsigned long base;
    // change the next 3 lines according to your victim and hook funtion.
    static int (*hooker_victim)(int a, int b) = (void*)0;
    hooker_victim = (void*)kallsyms_lookup_name("add_num");
    addr_new = hookers_piston;

    static int (*set_memory_rw)(unsigned long addr, int numpages) = (void*)0;
    set_memory_rw = (void*)kallsyms_lookup_name("set_memory_rw");
    if (hooker_victim == 0 || set_memory_rw == 0)
    {
        printk(KERN_INFO "unable to resolve the addresses\n");
        return 0;
    }
    //memcpy(hex_bytes, add_num, 8);
    addr = hooker_victim;
    hex_bytes = addr;
    base = (unsigned long)hooker_victim;

    set_memory_rw(base & PAGE_MASK, 1);

    // mov rax, addr
    hex_bytes[0] = 0x48;
    hex_bytes[1] = 0xc7;
    hex_bytes[2] = 0xc0;
    hex_bytes[3] = (0xFF & addr_new);
    hex_bytes[4] = (0xFF & (addr_new >> 8));
    hex_bytes[5] = (0xFF & (addr_new >> 16));
    hex_bytes[6] = (0xFF & (addr_new >> 24));
    // call rax
    hex_bytes[7] = 0xFF;
    hex_bytes[8] = 0xD0;
    // ret
    hex_bytes[9] = 0xc3;
    printk(KERN_INFO "Hooker implanted:)");
    //printk(KERN_INFO "modded hex bytes are 0x%02x, 0x%02x\n", (unsigned char)hex_bytes[0], (unsigned char)hex_bytes[1]);
    return  0;
}

static void my_exit(void)
{
    printk(KERN_INFO "Hooker left the game.\n");

    return;
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
