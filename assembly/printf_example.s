# PURPOSE:
#
# as printf_example.s -o printf_example.o
# ld printf_example.o -o printf_example -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2

.section .data

# This string is called the format string. It’s the first
# parameter, and printf uses it to find out how many parameters
# it was given, and what kind they are.
firststring:
 .ascii "Hello! %s is a %s who loves the number %d\n\0"

name:
 .ascii "Jonathan\0"

personstring:
 .ascii "person\0"

# This could also have been an .equ, but we decided to give it
# a real memory location
numberloved:
 .long 3

 .section .text
 .globl _start

_start:
 # note that the parameters are passed in the
 # reverse order that they are listed in the
 # function’s prototype.
 
 push numberloved   # This is the %d
 push $personstring # This is the second %s
 push $name # This is the first %s
 push $firststring # This is the format string in the prototype

 call printf
 push $0
 
 call exit
