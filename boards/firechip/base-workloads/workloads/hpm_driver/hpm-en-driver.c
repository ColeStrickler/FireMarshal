#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/smp.h>
#include <linux/cpumask.h>  
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/pid.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>


#ifdef __ASSEMBLER__
#define __ASM_STR(x)	x
#else
#define __ASM_STR(x)	#x
#endif

#define csr_read(csr)                                           \
	({                                                      \
		register unsigned long __v;                     \
		__asm__ __volatile__("csrr %0, " __ASM_STR(csr) \
				     : "=r"(__v)                \
				     :                          \
				     : "memory");               \
		__v;                                            \
	})


#define CSR_CYCLE			0xc00
#define CSR_TIME			0xc01
#define CSR_INSTRET			0xc02
#define scounteren          0x0106


int irq = 0;
static irqreturn_t my_irq_handler(int irq, void *dev_id) {
    // Code to handle the interrupt (e.g., read/write device registers)
    printk(KERN_INFO "Interrupt occurred!\n");
    return IRQ_HANDLED; // Return IRQ_HANDLED to indicate that it was handled
}





static int __init DriverLoad(void) {
    printk("DriverLoad() entry.\n");
    int ret = 0;

    int online_cpus = num_online_cpus();


    struct device_node *node;

    // Locate device node from the device tree
    node = of_find_compatible_node(NULL, NULL, "sifive,inclusivecache0");
    if (!node) {
        pr_err("Failed to find device node\n");
        return -ENODEV;
    }

    for (int i = 0; i < online_cpus; i++)
    {
        // Retrieve the IRQ mapped from the hardware interrupt number
        irq = of_irq_get(node, i);  // 0 = first interrupt in "interrupts" property
        if (irq < 0) {
            pr_err("Failed to get IRQ from device tree\n");
            return irq;
        }

        pr_info("Mapped hwirq to Linux IRQ: %d\n", irq);
        //printk("scounteren: 0x%x\n", csr_read(scounteren));
        //HPM_EN_USER();
        ret = request_irq(irq, my_irq_handler, 0, "memguard", NULL);
        if (ret) {
            printk(KERN_ERR "Failed to request IRQ %d --> %d\n", irq, ret);
            return ret;
        }
    }

    
    

    //printk("cycle: 0x%lx\n", csr_read(CSR_CYCLE));
    printk(KERN_INFO "DriverLoad() successful.\n");

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