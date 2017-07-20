.include "record_def.s"
.include "linux.s"

# PURPOSE: This function reads a record from the file
# descriptor
#
# INPUT: The file descriptor and a buffer
#
# OUTPUT: This function writes the data to the buffer
# and returns a status code.
#

# STACK LOCAL VARIABLES
 .equ ST_READ_BUFFER, 8
 .equ ST_FILEDES, 12
 .section .text
 .globl read_record
 .type read_record, @function

read_record:
 pushl %ebp                       # preserve stack frame base ptr
 movl %esp, %ebp                  # make stack ptr new base ptr
 pushl %ebx                       # preserve ebx
 movl $SYS_READ, %eax             # sys call into eax
 movl ST_FILEDES(%ebp), %ebx      # fd into ebx
 movl ST_READ_BUFFER(%ebp), %ecx  # buf ptr into ecx
 movl $RECORD_SIZE, %edx          # buf sz into edx
 int $LINUX_SYSCALL               # call read

 # NOTE - %eax has the return value, which we will
 # give back to our calling program
 popl %ebx                        # restore ebx
 movl %ebp, %esp
 popl %ebp
 ret
