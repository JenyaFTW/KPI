#define N 10

struct Queue {
    int arr[N];
    int front;
    int last;
};

struct Queue* initializeQueue() {
    struct Queue* q = malloc(sizeof(struct Queue));
    q->front = -1;
    q->last = -1;
    return q;
}

int isEmpty(struct Queue* q) {
    if (q->last == -1)
        return 1;
    else
        return 0;
}

void pushQueue(struct Queue* q, int value) {
    if (q->front == -1)
        q->front = 0;
    q->last++;
    q->arr[q->last] = value;
}

int popQueue(struct Queue* q) {
    int item;
    if (isEmpty(q)) {
        item = -1;
    }
    else {
        item = q->arr[q->front];
        q->front++;
        if (q->front > q->last) q->front = q->last = -1;
    }
    return item;
}