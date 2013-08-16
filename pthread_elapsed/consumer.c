#include "pthread.h"
#include "errno.h"
#include "stdio.h"

pthread_cond_t cv;
pthread_mutex_t mutex;
int length;
int queue[10];



void producer(void *param)
{
  time_t * item;
	for(int i = 0; i < 600; i++)
	{
		pthread_mutex_lock( &mutex );
		queue[length++] = i;
		pthread_cond_broadcast(&cv);
		pthread_mutex_unlock(&mutex);
		printf("Producer length : %d \n", i);
	}
}

void *consumer(void *param)
{

    for(int i = 0; i < 500; i++) {
        int seconds =  20;
        pthread_mutex_lock( & mutex );

        while(length == 0) {
					struct timespec now;
					now.tv_sec = time(0) + 1;
					now.tv_nsec = 0;
					printf("Time wait : %d ETIMEDOUT : %d \n",pthread_cond_timedwait(&cv, &mutex, &now),  ETIMEDOUT);
					if(pthread_cond_timedwait(&cv, &mutex, &now) == ETIMEDOUT)
					{
								seconds++;
								printf("In timedwait function, seconds : %d \n ", seconds);
					}
					printf("Length is zero, seconds : %d \n", seconds);
        }
				int item = queue[--length];
				if(seconds) { printf(" %i seconds waited \n", seconds); }
				pthread_mutex_unlock(&mutex);
				printf(" Received : %i \n", item);

    }
}
int main()
{

    pthread_t threadcp[2];
		pthread_mutex_init(&mutex, 0);

    pthread_cond_init(&cv, 0);
		length = 5;

		pthread_create(&threadcp[0], 0, consumer, 0);
 		pthread_create(&threadcp[1], 0, producer, 0);

   pthread_join(threadcp[0], 0);
   pthread_join(threadcp[1], 0);

	 pthread_mutex_destroy(&mutex);

	 pthread_cond_destroy(&cv);
}
