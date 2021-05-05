#define N 10

struct Stack {
    int arr[N];
    int top;
};

struct Stack* initializeStack() {
    struct Stack* stack = malloc(sizeof(struct Stack));
    stack->top = 0;
    return stack;
}

void pushStack(struct Stack* stack, int value) {
    if (stack->top < N) {
        stack->arr[stack->top] = value;
        stack->top++;
    }
}

void flush(struct Stack* stack) {
    stack->top--;
}

int top(struct Stack* stack) {
    if (stack->top > 0)
        return stack->arr[stack->top - 1];
    else return -1;
}

int isEmptyStack(struct Stack* stack) {
    if (stack->top == 0)
        return 1;
    else
        return 0;
}