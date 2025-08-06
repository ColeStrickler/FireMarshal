MODULE_NAME := hpm-en-driver
KERNEL_SRC := /home/c674s876/Documents/firesim/DOSvBRU-firesim/target-design/chipyard/software/firemarshal/boards/firechip/linux-fsim/
CROSS_COMPILE := riscv64-unknown-linux-gnu-
ARCH := riscv
PWD := $(CURDIR)
obj-m += $(MODULE_NAME).o
INCLUDES=./include/

driver: $(MODULE_NAME).ko

$(MODULE_NAME).ko : $(MODULE_NAME).o 
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) CROSS_COMPILE=$(CROSS_COMPILE) ARCH=$(ARCH) modules


$(MODULE_NAME).o : $(MODULE_NAME).c
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) CROSS_COMPILE=$(CROSS_COMPILE) ARCH=$(ARCH) modules


clean:
	rm ./wpuser-control ./$(MODULE_NAME).mod ./$(MODULE_NAME).ko ./Module.symvers ./modules.order ./$(MODULE_NAME).mod.o

install:
	sudo insmod ./$(MODULE_NAME).ko
