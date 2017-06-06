; nasm -f elf64 tiny03.asm 
; gcc -Wall -s -nostdlib tiny03.o
; wc -c a.out: 528 bytes

; To generate a list file:
;   nasm -f coff tiny03.asm -l tiny03.lst

BITS 32
GLOBAL _start
SECTION .text
_start:
    mov eax, 1
    mov ebx, 42
    int 0x80