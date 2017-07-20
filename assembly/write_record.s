.include "linux.s"
.include "record_def.s"

# PURPOSE: This function writes a record to
# the given file descriptor
#
# INPUT: The file descriptor and a buffer
#
# OUTPUT: This function produces a status code
#

# STACK LOCAL VARIABLES
 .equ ST_WRITE_BUFFER, 8
 .equ ST_FILEDES, 12
 .section .text
 .globl write_record
 .type write_record, @function

write_record:
 pushl %ebp                       # preserve stack frame base ptr
 movl %esp, %ebp                  # make stack ptr new base ptr
 pushl %ebx                       # preserve ebx
 movl $SYS_WRITE, %eax            # sys call into eax
 movl ST_FILEDES(%ebp), %ebx      # fd into ebx
 movl ST_WRITE_BUFFER(%ebp), %ecx # buf ptr into ecx
 movl $RECORD_SIZE, %edx          # buf sz into edx
 int $LINUX_SYSCALL

# NOTE - %eax has the return value, which we will
# give back to our calling program
 popl %ebx
 movl %ebp, %esp
 popl %ebp
 ret
