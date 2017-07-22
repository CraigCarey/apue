# PURPOSE:
#  This program writes the message "hello world" and exits
#
# BUILDING:
#       as hello_world_no_lib.s -o hello_world_no_lib.o
#       ld hello_world_no_lib.o -o hello_world_no_lib

 .include "linux.s"

 .section .data

helloworld:
 .ascii "hello world\n"

helloworld_end:
 .equ helloworld_len, helloworld_end - helloworld

 .section .text
 .globl _start
_start:
 movl $SYS_WRITE, %eax
 movl $STDOUT, %ebx
 movl $helloworld, %ecx
 movl $helloworld_len, %edx
 int $LINUX_SYSCALL
 
 movl $0, %ebx
 movl $SYS_EXIT, %eax
 int $LINUX_SYSCALL
