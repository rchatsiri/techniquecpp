#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>

typedef struct data
{
 char name[10];
 int age;
}data;

void sig_func(int sig)
{
 write(1, "Caught signal 11\n", 17);
 signal(SIGSEGV,sig_func);
}

void func(data *p)
{
 fprintf(stderr, "This is from thread function\n");
 strcpy(p->name,"Mr. Linux");
 p->age=30;
 sleep(2); // Sleep to catch the signal
}

int main()
{
 pthread_t tid;
 pthread_attr_t attr;
 data d;
 data *ptr = &d;

 signal(SIGSEGV,sig_func); // Register signal handler before going multithread
 pthread_attr_init(&attr);
 pthread_create(&tid,&attr,(void*)func,ptr);
 sleep(1); // Leave time for initialisation
 pthread_kill(tid,SIGSEGV);

 pthread_join(tid,NULL);
 fprintf(stderr, "Name:%s\n",ptr->name);
 fprintf(stderr, "Age:%d\n",ptr->age);
}
