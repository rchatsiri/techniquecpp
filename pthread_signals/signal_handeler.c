#include "signal.h"
#include "stdio.h"
#include "unistd.h"
#include "sys/wait.h"


volatile int go = 0;


void handler(int sig)
{

	go = 1;
	write(1, "Signal arrvied \n", 16);
}

int main()
{

	signal(SIGRTMIN+4, handler);
	pid_t f = fork();
	if(f == 0)
	{
		while(!go){ }
		printf("Child completed \n");
	}
	else
	{
		kill(f, SIGRTMIN+4);
		waitpid(f, 0, 0);
		printf("Parent Completed \n");
	}

}
