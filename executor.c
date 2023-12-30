#include "executor.h"
#include "async_errors.h"
#include <stdlib.h>

executor new_executor(){
    executor temp;
    temp.end = -1;
    for(int i=0; i<MAX_TASKS; i++){
        temp.tasks[i] = NULL; // initializing queue to contain only null pointers
    }
    return temp;
}

// enqueues task
void spawn_task(executor *ex, struct future_t *task){
    ex->end += 1;
    if(ex->end == MAX_TASKS)
        exit(TASK_LIMIT_EXCEEDING);
    ex->tasks[ex->end] = task;
}

// dequeues task
struct future_t *get_task(executor *ex){
    struct future_t* temp;
    temp = ex->tasks[0];
    for(int i=0; i<=ex->end; i++){
        if(i==MAX_TASKS-1){
            ex->tasks[MAX_TASKS-1] = NULL;
            break;
        }
        ex->tasks[i] = ex->tasks[i+1];
    }
    ex->end -= 1;
    return temp;
}

waker null_waker(){
    waker temp;
    temp.exec = NULL;
    return temp;
}