MODULE_NAME := rme-driver
KERNEL_SRC := /home/c674s876/Documents/firesim/dtu-firesim/chipyard/software/firemarshal/boards/firechip/linux
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
	rm ./wpuser-control ./$(MODULE_NAME).mod ./$(MODULE_NAME).ko ./$(MODULE_NAME).o ./Module.symvers ./modules.order ./$(MODULE_NAME).mod.o

install:
	sudo insmod ./$(MODULE_NAME).ko
