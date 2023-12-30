#include "executor.h"
#include "future.h"
#include <stdio.h>

poll_result poll_a(future* fut){
    if(fut->state[0]==0){
        fut->result = 0;
        return POLL_READY;
    }
    fut->state[0] -= 1;
    puts("Ran future A");
    fut->w.wake(&fut->w);
    return POLL_PENDING;
}

poll_result poll_b(future* fut){
    if(fut->state[0]==0){
        fut->result = 0;
        return POLL_READY;
    }
    fut->state[0] -= 1;
    puts("Ran future B");
    fut->w.wake(&fut->w);
    return POLL_PENDING;
}

int main(){
    executor main_exec = new_executor();
    int state_a[1] = {5};
    int state_b[1] = {3};
    future future_a = new_future(poll_a, null_waker(), state_a);
    future future_b = new_future(poll_b, null_waker(), state_b);

    spawn_task(&main_exec, &future_a);
    spawn_task(&main_exec, &future_b);


    start_executor(&main_exec);
    return 0;
}

/*
TODO:
    test with a future which works with a process in different thread
    implement async handlers for IO systems.

*/