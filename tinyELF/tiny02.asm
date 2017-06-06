; nasm -f elf64 tiny02.asm 
; gcc -Wall -s -nostartfiles tiny02.o
; wc -c a.out: 5224 bytes

; To generate a list file:
;   nasm -f coff tiny02.asm -l tiny02.lst

; exits with 104 for some reason?

BITS 32
EXTERN _exit
GLOBAL _start
SECTION .text
_start:
    push dword 42
    call _exit