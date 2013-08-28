#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t semaphore;
sem_t limit;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;

int queue[10];
int length;

void *producer(void * param)
{
	for(int i = 0; i < 50; i++)
	{

		//sem_wait(&limit);
		
		pthread_mutex_lock(&mutex);		

		queue[length++] = i;

		pthread_cond_broadcast(&cv);

		pthread_mutex_unlock(&mutex);

		//sem_post(&semaphore);

	}

}

void *consumer(void * param)
{
	for(int i = 0; i < 50; i++)
	{	

		int item;
		int go = 0;
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cv, &mutex);

		if(length > 0)
			{
				item = queue[--length];
				go = 1;
			}
	
		pthread_mutex_unlock(&mutex);
		if(go)
		{
			printf("Received : %i \n", item);
		}
	}

}


void write_filebuff()
{

}

void thread_execuate()
{

}

void thread_manager()
{
		
}


int main()
{
	pthread_condattr_t cva;
	pthread_condattr_init(&cva);
	pthread_condattr_setpshared(&cva, PTHREAD_PROCESS_SHARED);

	pthread_cond_init(&cv, &cva);
	
	pthread_t threads[2];
	
	//sem_init(&semaphore, 0, 0);
	//sem_init(&limit, 0, 10);

	pthread_create(&threads[0], 0, producer, 0);
	pthread_create(&threads[1], 0, consumer, 0);

	pthread_join(threads[0], 0);
	pthread_join(threads[1], 0);

	//sem_destroy(&limit);
	//sem_destroy(&limit);
	
	pthread_cond_destroy(&cv);
}

