#pragma once
#define MAX_TASKS 100

#include<stdlib.h>

typedef enum {POLL_PENDING, POLL_READY} poll_result; 
struct future_t;


typedef struct {
    struct future_t *tasks[MAX_TASKS];
    int end;
}executor;

struct waker_t;

typedef void (*wake_fn)(struct waker_t *self);

typedef struct waker_t{
    executor *exec;
    wake_fn wake;
    struct future_t *fut;

}waker;

typedef poll_result (*poll_fn)(struct future_t*);

void spawn_task(executor*, struct future_t*);
struct future_t *get_task(executor*);

executor new_executor();
waker null_waker();
void start_executor(executor *ex);