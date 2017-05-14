#include <pthread.h>
#include <stdio.h>

void *func(void *arg)
{
    printf("child thread says %s\n", (char *)arg);
    sleep(1000);
    pthread_exit((void *)99);
}

int main()
{
    pthread_t handle;
    int exitcode;

    pthread_create(&handle, NULL, func, "hi!");
    printf("primary thread says hello\n");
    pthread_join(handle, (void **)&exitcode);
    printf("exit code %d\n", exitcode);
}
