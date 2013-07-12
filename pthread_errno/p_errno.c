#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void *thread1(void *param)
{
    FILE *fhandle = fopen(".", "w");
    int i;

    if(!fhandle) {
        printf("Thread1 %4i\n", errno);
    } else {
        fclose(fhandle);
    }
}

int main()
{
    pthread_t thread_data;
    int i;
    pthread_create(&thread_data, 0, thread1, 0);
    FILE *fhandle = fopen("", "r");

    if(!fhandle) {
        printf(" Main %4i\n", errno);
    } else {
        fclose(fhandle);
    }

    pthread_join(thread_data, 0);
}
