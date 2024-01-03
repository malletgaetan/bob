#!/usr/bin/env bash

make -C ./kernel/
BS=512
KERNEL_BYTE_SIZE=$(stat --printf="%s" kernel/kernel)
KSIZE=$((($KERNEL_BYTE_SIZE / $BS) + 1))
nasm -f bin -D KSIZE=$KSIZE bootloader/bootloader.s -o bootloader
cat bootloader/bootloader kernel/kernel /dev/zero | dd of=floppy bs=$BS count=$(($KSIZE + 1))
qemu-system-i386 -fda floppy
make fclean -C ./kernel/
rm bootloader floppy

