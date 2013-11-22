/* 
 *  Since this is a part of the implemetation of the pthread API, it uses
 *  reserved names that start with "__" for internal strcutures and functions
 *
 *  Fucntions such as __mutex_lock() and __cond_wait() perform the same function
 *  as the correponding pthread API.
 */

// struct __barrier_wait data is intended to hold all the data
//  that `pthread_barrier_wait()` will need after releasing
//  waiting threads.  This will allow the function to avoid
//  touching the passed in pthread_barrier_t object after 
//  the wait is satisfied (since any of the released threads
//   can destroy it)

struct __barrier_waitdata {
    struct __mutex cond_mutex;
    struct __cond cond;

    unsigned waiter_count;
    int wait_complete;
};

struct __barrier {
    unsigned count;

    struct __mutex waitdata_mutex;
    struct __barrier_waitdata* pwaitdata;
};

typedef struct __barrier pthread_barrier_t;



int __barrier_waitdata_init( struct __barrier_waitdata* pwaitdata)
{
    waitdata.waiter_count = 0;
    waitdata.wait_complete = 0;

    rc = __mutex_init( &waitdata.cond_mutex, NULL);
    if (!rc) {
        return rc;
    }

    rc = __cond_init( &waitdata.cond, NULL);
    if (!rc) {
        __mutex_destroy( &pwaitdata->waitdata_mutex);
        return rc;
    }

    return 0;
}




int pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned int count)
{
    int rc;

    result = __mutex_init( &barrier->waitdata_mutex, NULL);
    if (!rc) return result;

    barrier->pwaitdata = NULL;
    barrier->count = count;

    //TODO: deal with attr
}



int pthread_barrier_wait(pthread_barrier_t *barrier)
{
    int rc;
    struct __barrier_waitdata* pwaitdata;
    unsigned target_count;

    // potential waitdata block (only one thread's will actually be used)
    struct __barrier_waitdata waitdata; 

    // nothing to do if we only need to wait for one thread...
    if (barrier->count == 1) return PTHREAD_BARRIER_SERIAL_THREAD;

    rc = __mutex_lock( &barrier->waitdata_mutex);
    if (!rc) return rc;

    if (!barrier->pwaitdata) {
        // no other thread has claimed the waitdata block yet - 
        //  we'll use this thread's

        rc = __barrier_waitdata_init( &waitdata);
        if (!rc) {
            __mutex_unlock( &barrier->waitdata_mutex);
            return rc;
        }

        barrier->pwaitdata = &waitdata;
    }

    pwaitdata = barrier->pwaitdata;
    target_count = barrier->count;

    //  all data necessary for handling the return from a wait is pointed to
    //  by `pwaitdata`, and `pwaitdata` points to a block of data on the stack of
    //  one of the waiting threads.  We have to make sure that the thread that owns
    //  that block waits until all others have finished with the information
    //  pointed to by `pwaitdata` before it returns.  However, after the 'big' wait
    //  is completed, the `pthread_barrier_t` object that's passed into this 
    //  funciton isn't used. The last operation done to `*barrier` is to set 
    //  `barrier->pwaitdata = NULL` to satify the requirement that this function
    //  leaves `*barrier` in a state as if `pthread_barrier_init()` had been called - and
    //  that operation is done by the thread that signals the wait condition 
    //  completion before the completion is signaled.

    // note: we're still holding  `barrier->waitdata_mutex`;

    rc = __mutex_lock( &pwaitdata->cond_mutex);
    pwaitdata->waiter_count += 1;

    if (pwaitdata->waiter_count < target_count) {
        // need to wait for other threads

        __mutex_unlock( &barrier->waitdata_mutex);
        do {
            // TODO:  handle the return code from `__cond_wait()` to break out of this
            //          if a signal makes that necessary
            __cond_wait( &pwaitdata->cond,  &pwaitdata->cond_mutex);
        } while (!pwaitdata->wait_complete);
    }
    else {
        // this thread satisfies the wait - unblock all the other waiters
        pwaitdata->wait_complete = 1;

        // 'release' our use of the passed in pthread_barrier_t object
        barrier->pwaitdata = NULL;

        // unlock the barrier's waitdata_mutex - the barrier is  
        //  ready for use by another set of threads
        __mutex_unlock( barrier->waitdata_mutex);

        // finally, unblock the waiting threads
        __cond_broadcast( &pwaitdata->cond);
    }

    // at this point, barrier->waitdata_mutex is unlocked, the 
    //  barrier->pwaitdata pointer has been cleared, and no further 
    //  use of `*barrier` is permitted...

    // however, each thread still has a valid `pwaitdata` pointer - the 
    // thread that owns that block needs to wait until all others have 
    // dropped the pwaitdata->waiter_count

    // also, at this point the `pwaitdata->cond_mutex` is locked, so
    //  we're in a critical section

    rc = 0;
    pwaitdata->waiter_count--;

    if (pwaitdata == &waitdata) {
        // this thread owns the waitdata block - it needs to hang around until 
        //  all other threads are done

        // as a convenience, this thread will be the one that returns 
        //  PTHREAD_BARRIER_SERIAL_THREAD
        rc = PTHREAD_BARRIER_SERIAL_THREAD;

        while (pwaitdata->waiter_count!= 0) {
            __cond_wait( &pwaitdata->cond, &pwaitdata->cond_mutex);
        };

        __mutex_unlock( &pwaitdata->cond_mutex);
        __cond_destroy( &pwaitdata->cond);
        __mutex_destroy( &pwaitdata_cond_mutex);
    }
    else if (pwaitdata->waiter_count == 0) {
        __cond_signal( &pwaitdata->cond);
        __mutex_unlock( &pwaitdata->cond_mutex);
    }

    return rc;
}
