#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

volatile int go = 0;
struct sigaction oldhandler;


void handler(int sig, siginfo_t * info, void * context)
{
	go = (int)info->si_value.sival_int;
	write(1, "Signal arrived\n", 16);
}

int main()
{
	struct sigaction newhandler;
	newhandler.sa_sigaction = handler;
	newhandler.sa_flags = SA_SIGINFO;
	sigemptyset(&newhandler.sa_mask);
	sigaction(SIGRTMIN+4, &newhandler, &oldhandler);

	pid_t f = fork();
	if(f == 0)
	{
		while(!go){}
		printf("Child process completed go = %i\n", go);
	}
	else
	{
		union sigval value;
	  value.sival_int = 7;
		sigqueue(f, SIGRTMIN + 4, value);
		waitpid(f, 0, 0);
		printf("Parent complted \n");	
	}
	
}
