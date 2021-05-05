#ifndef QUEUE_H_
#define QUEUE_H_

struct Stack;
struct Stack* initializeStack();
void pushStack(struct Stack* stack, int value);
void flush(struct Stack* stack);
int top(struct Stack* stack);
int isEmptyStack(struct Stack* stack);

#endif