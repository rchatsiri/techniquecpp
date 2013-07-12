#include <stdio.h> 
#include <pthread.h>

int count = 0;
int  i    = 0;
pthread_spinlock_t lock;

void lockandunlock()
{
	int i = 10000;
	while(i == 0)
	{
		if(pthread_spin_trylock(&lock))
		{
				i++;
				pthread_spin_unlock(&lock);
				printf("Trylock... \n");
		}
		else
		{
				count++;
		}
		printf("Fail to try lock : %d \n", count);
	}
}

int main()
{

	pthread_spin_init(&lock, PTHREAD_PROCESS_SHARED);
	lockandunlock();
	pthread_spin_destroy(&lock);

}
