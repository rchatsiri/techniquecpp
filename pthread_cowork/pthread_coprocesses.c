#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <unistd.h>

#define EMPTY_DATA    0
#define CONTAIN_DATA  1

#define IDLE_THREAD    0
#define ACTIVE_THREAD  1

#define PROXY_UNLOCK_BUF 0



// status 0 to idle, 1 to processesi

struct thread_profile {
		int thread_num;
		int status;
    char *file_name;
};


// Status 1 each structs that mean. Tdetail contains buffer
struct thread_profile *tbuffer[4];

pthread_cond_t exe_cond =  PTHREAD_COND_INITIALIZER;
pthread_mutex_t exe_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t ran_mutex = PTHREAD_MUTEX_INITIALIZER;


char *path_file[4];

void work_scanfile(void *param)
{
    printf("@@ Work_execuate @@\n");

    struct thread_profile *tpf = (struct thread_profile *)param;

    pthread_mutex_lock(&exe_mutex);

  	while(1)
		{
				for(int count_buf = 0; count_buf < 4; count_buf++)
				{
					struct thread_profile * tbuf = tbuffer[count_buf];
					if(tbuf->status == CONTAIN_DATA 
							&& tbuf->thread_num == PROXY_UNLOCK_BUF
							&& tpf->thread_num == PROXY_UNLOCK_BUF)
					{
						  //tbuf->read_by_thread = tpf->thread_num;
							tbuf->status = EMPTY_DATA;
							tbuf->thread_num = pthread_self();
							tpf->thread_num  = pthread_self();
	
							printf("@@ Work_execuate, tbuf change to Empty data, thread_num : [ %d ], buffer_index [ %d ]  \n", pthread_self(), count_buf);

							sleep(2);
						  tpf->thread_num  = PROXY_UNLOCK_BUF;
								//broadcast to next thread
					}

					if(tbuf->status == EMPTY_DATA)	pthread_cond_wait(&exe_cond, &exe_mutex);

				}
		} 
		printf("---     end   ---\n");
    pthread_mutex_unlock(&exe_mutex);
}

void thread_execuate()
{

    while(1) {

        for(int count_file = 0; count_file < 4; count_file++) {
            pthread_mutex_lock(&exe_mutex);
            struct thread_profile *tbuf = tbuffer[count_file];
						//wait to next job
					  if(tbuf->status == EMPTY_DATA)
						{
								printf("Buffer reuse after tbuf id : %d \n", tbuf->thread_num);
								tbuf->status = CONTAIN_DATA;
								tbuf->thread_num = PROXY_UNLOCK_BUF;
								printf("Get new buffer to tbuf \n");
								pthread_cond_broadcast(&exe_cond);
								//pthread_cond_wait(&exe_cond, &exe_mutex);
						}	
            pthread_mutex_unlock(&exe_mutex);
        }
    }

}


void ranbuffer(void *param)
{
    pthread_mutex_lock(&ran_mutex);

    for(int count_td  = 0; count_td < 4; count_td++) {
        int ran_num = rand() % 2;

        if(ran_num == 2) ran_num = ran_num -2;

        tbuffer[count_td]->status = ran_num ;
        printf("Random status tbuffer [ %d ], status : [%d] \n", count_td, ran_num);
    }

    pthread_mutex_unlock(&ran_mutex);
}

int main()
{

    pthread_t threads[4];
		pthread_t threads_getwork;
    pthread_t ramdom_status_buffer;

    pthread_cond_init(&exe_cond, 0);
    pthread_mutex_init(&exe_mutex, 0);
    pthread_mutex_init(&ran_mutex, 0);

    // create file buffer
    for(int count_td  = 0; count_td < 4; count_td++) {
        tbuffer[count_td] = (struct thread_profile *)malloc(sizeof(tbuffer));
        tbuffer[count_td]->status = CONTAIN_DATA;
				tbuffer[count_td]->thread_num = PROXY_UNLOCK_BUF;
    }

    struct thread_profile *tpf[4];

    for(int count_t = 0; count_t < 4; count_t++) {
        tpf[count_t] = (struct thread_profile *)malloc(sizeof(tpf));
        tpf[count_t]->status = IDLE_THREAD; // not procecced.
        tpf[count_t]->file_name = (char *)malloc(sizeof(char *));
        tpf[count_t]->file_name = "/home/test";
				tpf[count_t]->thread_num = PROXY_UNLOCK_BUF;
				//threads[count_t] = (struct thread_profile*)malloc(sizeof(threads));
        pthread_create(&threads[count_t], 0, work_scanfile, tpf[count_t]);

        printf("### Main, Create thread [%d] completed \n", count_t);
    }

			pthread_create(&threads_getwork, 0, thread_execuate, 0);
  
    for(int count_j = 0; count_j < 4; count_j++) pthread_join(threads[count_j], 0);


    pthread_mutex_destroy(&exe_mutex);
    pthread_cond_destroy(&exe_cond);
    pthread_mutex_destroy(&ran_mutex);
}
