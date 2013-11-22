#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUMTHREADS 20 /* number of threads to create */

pthread_mutex_t exe_mutex = PTHREAD_MUTEX_INITIALIZER;


typedef struct node node;
typedef struct queue queue;

struct node {
    char *name;
    node *next;
};

struct queue {
    node *head;
    node *tail;
};

/* pop: remove and return first name from a queue */
char *pop(queue *q)
{
    if (q->head == NULL)
        return NULL;
    char *name = q->head->name;
    node *tmp = q->head;
    q->head = q->head->next;
    free(tmp);
    return name;
}

/* push: add name to the end of the queue */
int push(queue *q, char *name)
{
    node *new = malloc(sizeof(node));
    if (new == NULL)
        return -1;
    new->name = name;
    new->next = NULL;
    if (q->tail != NULL)
        q->tail->next = new;

    q->tail = new;
    if (q->head == NULL) /* first value */
        q->head = new;
    return 0;
}

/* printname: get a name from the queue, and print it. */
void *printname(void *sharedQ)
{
	  pthread_mutex_lock(&exe_mutex);
    queue *q = (queue *) sharedQ;
    char *name = pop(q);
    if (name == NULL)
        pthread_exit(NULL);
    printf("Name : %s, pthread_id : %li \n ",name, pthread_self());
		pthread_mutex_unlock(&exe_mutex);
    pthread_exit(NULL);
	
}

int main()
{
    size_t i;
    int rc;
    pthread_t threads[NUMTHREADS];
		pthread_mutex_init(&exe_mutex, 0);

    char *names[] = {
        "yasar",
        "arabaci",
        "osman",
        "ahmet",
        "mehmet",
        "zeliha"
    };

    queue *q = malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;

    /* number of elements in the array */
    size_t numelems = sizeof(names) / sizeof(char *);

    for (i = 0; i < numelems; i++) /* push each name */
        push(q, names[i]);

    for (i = 0; i < NUMTHREADS; i++) { /* fire up threads */
        rc = pthread_create(&threads[i], NULL, printname,
                (void *)q);
        if (rc) {
            printf("Error, return code from pthread is %d\n", rc);
            exit(-1);
        }
    }
		pthread_mutex_destroy(&exe_mutex);
    pthread_exit(NULL);
}
