; nasm -f elf64 tiny04.asm 
; ld -s tiny04.o
; wc -c a.out: 344 bytes

; To generate a list file:
;   nasm -f coff tiny04.asm -l tiny04.lst
;
; segfaults for some reason

BITS 32
GLOBAL _start
SECTION .text
_start:
    xor eax, eax
    inc eax
    mov bl, 42
    int 0x80