#ifndef QUEUE_H_
#define QUEUE_H_

struct Queue;
struct Queue* initializeQueue();
int isEmpty(struct Queue* q);
void pushQueue(struct Queue* q, int value);
int popQueue(struct Queue* q);

#endif