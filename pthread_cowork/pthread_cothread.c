#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

pthread_cond_t my_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t my_cond_m = PTHREAD_MUTEX_INITIALIZER;

int * next_work = NULL;
int all_work_done = 0;

void * worker(void * arg)
{

    int * my_work = NULL;

    while(!all_work_done)
    {
        pthread_mutex_lock(&my_cond_m);

        if(next_work == NULL)
        {
						printf("-- Worker Boardcast, pthread_id : %d  \n", (int)(pthread_self()%100));
            // Signal producer to give work
            pthread_cond_broadcast(&my_cond);

            // Wait for work to arrive
            // It is wrapped in a while loop because the condition 
            // might be triggered by another worker thread intended 
            // to wake up the producer
            while(!next_work && !all_work_done)
						{
								printf("-- Worker in wait \n");
                pthread_cond_wait(&my_cond, &my_cond_m);
								printf("-- Worker out of wait : pthread_id : %d \n", (int)(pthread_self()%100));
						}
        }

        // Work has arrived, cache it locally so producer can 
        // put in next work ASAP
        my_work = next_work;
        next_work = NULL;
        pthread_mutex_unlock(&my_cond_m);

        if(my_work)
        {
            printf("Worker ID : %d consuming work: %d\n", (int)(pthread_self() % 100), *my_work);
						printf("-------------------\n");
            free(my_work);
        }
    }

    return NULL;
}

int * create_work()
{
    int * ret = (int *)malloc(sizeof(int));
    assert(ret);
    *ret = rand() % 100;
    return ret;
}

void * producer(void * arg)
{
		printf("-- Producer start.. \n");
    int i;

    for(i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&my_cond_m);
        while(next_work != NULL)
        {
						printf("--@@@ Producer is  boardcast and wait condition \n");
            // There's still work, signal a worker to pick it up
            pthread_cond_broadcast(&my_cond);

            // Wait for work to be picked up
            pthread_cond_wait(&my_cond, &my_cond_m);
			
						printf("--@@@ End Producer is  boardcast and wait condition : %d \n", (int)(pthread_self() % 100));

        }

        // No work is available now, let's put work on the queue
        next_work = create_work();
        printf("Producer: Created work %d, count_work : %d \n", *next_work, i);

        pthread_mutex_unlock(&my_cond_m);
    }

    // Some workers might still be waiting, release them
    pthread_cond_broadcast(&my_cond);

    all_work_done = 1;
    return NULL;
}

int main()
{
    pthread_t t1, t2, t3, t4;

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);
    pthread_create(&t3, NULL, worker, NULL);
    pthread_create(&t4, NULL, worker, NULL);

		
    producer(NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    return 0;
}
