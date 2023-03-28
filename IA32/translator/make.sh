#!/bin/bash
nasm -f elf32 $1.s -o a.o && ld -m elf_i386 a.o && ./a.out
