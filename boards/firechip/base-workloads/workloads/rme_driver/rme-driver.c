#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h> // For ioremap()
#include <linux/fs.h>
#include <linux/uaccess.h> // For copy_to_user()
#include <linux/mm.h>      // For VM flags


#define RESERVED_MEM_START 0x110000000ULL
#define RESERVED_MEM_SIZE 0x1000


static int __init DriverLoad(void) {

    //printk("cycle: 0x%lx\n", csr_read(CSR_CYCLE));
    printk(KERN_INFO "DriverLoad() successful.\n");
    void __iomem *reserved_mem;

    // Map the reserved memory region to the kernel's address space
    reserved_mem = ioremap(RESERVED_MEM_START, RESERVED_MEM_SIZE);
    if (!reserved_mem) {
        pr_err("Failed to map reserved memory region\n");
        return -ENOMEM;
    }

    // Access the reserved memory (example)
    pr_info("Reserved memory region mapped at: %p\n", reserved_mem);


    for (int i = 0; i < RESERVED_MEM_SIZE; i += sizeof(int))
    {
        pr_info("Read reserved memory: 0x%x\n", ioread32(reserved_mem + i));
    }


    return 0;
}

static void __exit DriverUnload(void) {
    printk(KERN_INFO "Driver unloaded successfully\n");
}



module_init(DriverLoad);
module_exit(DriverUnload);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cole Strickler");
MODULE_DESCRIPTION("Cache Way Partitioning for RaspberryPi5");