#include <stdlib.h>
#include "stack.h"
#include <stdio.h>

#define STACK_SIZE 100

struct stack {
    int array[STACK_SIZE];
    int size;
};


struct stack *stack_init() {
    struct stack *s = malloc(sizeof(struct stack));

    if (s == NULL) {
        return 1;
    }

    s->size=0;
    return s;
}

void stack_cleanup(struct stack *s) {
    s->size = 0;
    free(s);
}

int stack_push(struct stack *s, int c) {
    if (s == NULL) {
        return 1;
    }

    if (s->size < STACK_SIZE) {
        s->array[s->size] = c;
        s->size++;
    }
    else {
        return 1;
    }
    return 0;
}

int stack_pop(struct stack *s) {
    if (s == NULL) {
        return -1;
    }

    if (s->size == 0) {
        return -1;
    }

    else {
        int x = s->array[s->size - 1];
        s->size--;
        return x;
    }

    return 0;
}

int stack_peek(struct stack *s) {
    if (s == NULL) {
        return -1;
    }

    if (s->size == 0) {
        return -1;
    }
    return s->array[(s->size)-1];
}


int stack_empty(struct stack *s) {
    if (s == NULL) {
        return -1;
    }

    if (s->size == 0) {
        return 1;
    }

    if (s->size > 0) {
        return 0;
    }

    return -1;
}

int stack_size(struct stack *s) {
    if (s == NULL) {
        return -1;
    }

    return s->size;
}
