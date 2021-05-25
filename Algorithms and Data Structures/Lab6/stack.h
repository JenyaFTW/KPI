struct stack;
struct stack* initStack();
void pushStack(struct stack* stack, int value);
void flush(struct stack* stack);
int top(struct stack* stack);
int isEmptyStack(struct stack* stack);