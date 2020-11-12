isomake: myos.c start.asm myos.ld multiboot_header.asm
	gcc -m32 -c myos.c;
	nasm -f elf32 start.asm;
	nasm -f elf32 multiboot_header.asm;
	ld -m elf_i386 -o myos.bin -T myos.ld multiboot_header.o start.o myos.o;
	mv myos.bin ./myrom/boot/;
	grub-mkrescue -o myos.iso myrom;
