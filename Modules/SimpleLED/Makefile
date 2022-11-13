obj-m := driver.o
 
KDIR = /lib/modules/$(shell uname -r)/build

CC = gcc
 
 
default: app
	make -C $(KDIR)  M=$(shell pwd) modules
	
app: app.c
	$(CC) app.c -o app
 
clean:
	rm -rf *.o *.ko .*.cmd *.mod.c *~ core .tmp_versions Module.symvers modules.order app
	
