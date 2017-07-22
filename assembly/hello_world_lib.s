# as hello_world_lib.s -o hello_world_lib.o
# ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o hello_world_lib hello_world_lib.o -lc

 .section .data

helloworld:
 .ascii "hello world\n\0"

 .section .text
 .globl _start

_start:
 mov $helloworld, %rdi
 call printf

 mov $0, %rdi
 call exit
