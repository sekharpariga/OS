GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore		# 32 bit
ASPARAMS = --32			# 32 bit
LDPARAMS = -melf_i386
obj-m = hello.o
objects = loader.o gdt.o interrupts.o interruptstubs.o port.o keyboard.o kernel.o

%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o : %.s
	as $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: mykernel.bin
	cp $< /boot/mykernel.bin

mod:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin ' >> iso/boot/grub/grub.cfg
	echo '  boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=myOS.iso iso
	rm -rf iso

cp: iso
	cp ./myOS.iso /media/sf_nerd

run: mykernel.iso
	(killall VirtualBox && sleep 2) || true
	VirtualBox --startvm "My OS" &

.PHONY:clean
clean:
	rm -f $(objects) myOS.iso mykernel.bin *.out
