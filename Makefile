ifeq ($(KERNELRELEASE),)
		KERNELDIR ?= /lib/modules/$(shell uname -r)/build
		PWD := $(shell pwd)

modules:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules EXTRA_CFLAGS="-g -DDEBUG"
modules_install:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
		rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions

.PHONY: modules modules_install clean

else
        # called from kernel build system: just declare what our modules are
		obj-m := call_hooker.o test_export.o test_caller.c
endif
