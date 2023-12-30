#include "executor.h"

typedef struct future_t{
    poll_fn pfn;
    waker w;
    int *state; // wish i had generics
    int result;
}future;

future new_future(poll_fn, waker, int*);
