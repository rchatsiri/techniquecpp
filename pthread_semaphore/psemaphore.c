#include "pthread.h"
#include "stdio.h"
#include "semaphore.h"

sem_t	semaphore;

pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

int queue[200];
int	queueLength;

void * producer(void * param)
{
  int i;
	for( i = 0; i < 250; i++)
	{

		pthread_mutex_lock(&mutex);
		queue[queueLength++]  = i;
		pthread_mutex_unlock(&mutex);
		printf("Proceducer : %d ", i);
		//Signal Semaphore
		sem_post(&semaphore);
	}
	printf("End of producer \n");
}

void *consumer(void * param)
{
  int i; 
	for(i = 0; i < 250; i++)
	{
		int item;
		if(queueLength == 0)
		{
			printf("Consumer wait... \n");
			sem_wait(&semaphore);
			
		}

		pthread_mutex_lock(&mutex);
		item = queue[queueLength--];
		pthread_mutex_unlock(&mutex);
		printf("Received : %i ", item);
	}
	printf("End of consumer \n");
}

int main()
{
	pthread_t threads[2];

	sem_init(&semaphore, 0, 0);
	
	pthread_create(&threads[0], 0, producer, 0);
	pthread_create(&threads[1], 0, consumer, 0);

	pthread_join(threads[0], 0);
	pthread_join(threads[1], 0);
	
	sem_destroy(&semaphore);

}

