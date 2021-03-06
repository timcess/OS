disk: bootblock disk.img kernel_block
	dd if=bootblock of=disk.img bs=512 count=1 conv=notrunc
	dd if=kernel_block of=disk.img bs=512 count=10 seek=1 conv=notrunc

bootblock: bootblock.asm
	nasm -f bin -o bootblock bootblock.asm

disk.img:
	dd if=/dev/zero of=disk.img bs=1M count=1

kernel_block: start.o protected.o kernel.o interrupts.o interrupts_stubs.o multitasking.o
	ld -melf_i386 --oformat=binary -Tlinker.ld -o $@ $^

start.o: start.asm
	nasm -felf -o $@ $<

kernel.o: kernel.c
	gcc -m32 -nostdlib -nodefaultlibs -nostartfiles -c -o $@ $<

protected.o: enter_protected.c
	gcc -m32 -nostdlib -nodefaultlibs -nostartfiles -c -o $@ $<

interrupts_stubs.o: interrupts.asm
	nasm -felf -o $@ $<

interrupts.o: interrupts.c
	gcc -m32 -O -nostdlib -nodefaultlibs -nostartfiles -c -o $@ $<

multitasking.o: multitasking.c
	gcc -m32 -nostdlib -nodefaultlibs -nostartfiles -c -o $@ $<

run: bochs.txt
	bochs -qf bochs.txt

clean:
	rm -f disk.img bootblock *~ *.o

