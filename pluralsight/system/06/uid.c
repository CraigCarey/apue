/* Program to demonstrate real and effective IDs */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void main()
{
    printf("Real      UID = %d\n", getuid());
    printf("Effective UID = %d\n", geteuid());

    /* See if we can open hosts file for writing */
    printf("open: %d\n", open("/etc/hosts", O_RDWR));

    /* access() tests what the real user can do */
    printf("access: %d\n", access("/etc/hosts", W_OK));

    /* Now drop our root privilege and try again */
    seteuid(getuid());

    printf("Real      UID = %d\n", getuid());
    printf("Effective UID = %d\n", geteuid());

    /* See if we can open hosts file for writing */
    printf("open: %d\n", open("/etc/hosts", O_RDWR));

    /* access() tests what the real user can do */
    printf("access: %d\n", access("/etc/hosts", W_OK));
}
