; nasm -f elf64 tiny01.asm 
; gcc -Wall -s tiny01.o
; wc -c a.out: 6304 bytes

; To generate a list file:
;   nasm -f coff tiny01.asm -l tiny01.lst

BITS 32
GLOBAL main
SECTION .text
main:
    mov eax, 42
    ret