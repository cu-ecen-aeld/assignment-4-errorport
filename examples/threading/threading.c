#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    struct thread_data* tdata = (struct thread_data *)thread_param;
    int rc = 0;

    usleep(tdata->wait_to_obtain_ms * 1000);

    rc = pthread_mutex_lock(tdata->mtx);
    if(rc) {
        printf("Failed to lock mutex [%d]\n", rc);
        goto threadfunc_exit;
    }

    usleep(tdata->wait_to_release_ms * 1000);
    tdata->thread_complete_success |= true;

    rc = pthread_mutex_unlock(tdata->mtx);
    if(rc) {
        printf("Failed to unlock mutex [%d]\n", rc);
    }

threadfunc_exit:
    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{

    struct thread_data* tdata = (struct thread_data*)malloc(sizeof(struct thread_data));
    tdata->mtx = mutex;
    tdata->wait_to_obtain_ms = wait_to_obtain_ms;
    tdata->wait_to_release_ms = wait_to_release_ms;

    int rc = pthread_create(thread, NULL, threadfunc, (void*)tdata);

    return !rc;
}

