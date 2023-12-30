#include "future.h"
#include "executor.h"
#include<stdlib.h>

future new_future(poll_fn pfn, waker w, int* state){
    future temp;
    temp.pfn = pfn;
    temp.w = w;
    temp.state = state;
    return temp;
}

// simple wake function to add the future back to the executor's queue
void wake(waker *self){
    spawn_task(self->exec, self->fut);
}

void start_executor(executor *ex){
    wake_fn simple_wake_fn = wake;
    for(;;){
        struct future_t *f = get_task(ex);
        if(f == NULL) // out of tasks to run
            return;
        else {
            waker local_waker;
            local_waker.exec = ex;
            local_waker.fut = f;
            local_waker.wake = simple_wake_fn;
            f->w = local_waker;
            f->pfn(f);
        }

    }
}