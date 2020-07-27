#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

/** checks precedence of given operator; brackets have special
 * precedences to account for special functionality of the algorithm.
**/
int check_operator(char op) {
    switch(op) {
      case '^' :
         return 50;
      case '*' :
         return 40;
      case '/':
         return 40;
      case '~' :
         return 40;
      case '+' :
         return 30;
      case '-' :
         return 30;
      case '(' :
         return 5;
      case ')' :
         return 25;
      case '=' :
         return 10;
      default :
         return 0;
   }
}

int main(int argc, char *argv[]) {
    // check if two command line arguments were given
    if (argc != 2) {
        printf("usage: %s \"infix_expr\"\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    int push = 0;
    int pop = 0;
    int max = 0;
    int size = 0;

    // initialize stack data structure
    struct stack *s = stack_init();

    for (int i = 0; i < strlen(input); i++) {
        if (isalpha(input[i])) {
            return 1;
        }
    }

    for (int i = 0; i < strlen(input); i++) {
        // keep track of maximum of stack
        size = stack_size(s);
        if (size > max) {
            max = size;
        }

        // write down character if it is a number
        if isdigit(input[i]) {
            printf("%c", input[i]);
            if (isdigit(input[i + 1])) {
                printf("%c", input[i + 1]);
                i++;
                if (isdigit(input[i + 1])) {
                    printf("%c", input[i + 1]);
                    i++;
                }
            }
            printf(" ");
        }
        else if (input[i] == ' ') {
            i++;
        }

        else {
            // check precendence if stack is non-empty
            if (stack_empty(s) == 0) {
                char op = stack_peek(s);

                // if precedence of operator is higher than precedence of operator on stack: push
                if (check_operator(input[i]) > check_operator(op)) {
                    stack_push(s, input[i]);
                    push++;
                }

                // if operator is a left bracket, push to stack
                else if (check_operator(input[i]) == 5) {
                    stack_push(s, input[i]);
                    push++;
                }

                // if operator is a right bracket, clean stack till last left bracket
                else if (input[i] == ')') {
                    while (check_operator(stack_peek(s)) != 5) {
                        printf("%c ", stack_peek(s));
                        stack_pop(s);
                        pop++;
                    }
                    stack_pop(s);
                    pop++;
                }
                // else, clean stack until operator with lower precedence
                else {
                    while (check_operator(input[i]) <= check_operator(stack_peek(s))) {
                        printf("%c ", stack_peek(s));
                        stack_pop(s);
                        pop++;
                    }
                }
            }

            // push operator to stack if stack is empty
            else if (stack_empty(s) == 1) {
                stack_push(s, input[i]);
                push++;
                char op = stack_peek(s);
            }
        }
    }

    // pop stack items untill stack is empty
    while (stack_empty(s) == 0) {
        char left = stack_pop(s);
        if (left == ')') {
        }
        else {
            printf("%c ", left);
            pop++;
        }
    }

    // clean stack
    stack_cleanup(s);
    printf("\n");
    fprintf(stderr, "stats %i %i %i\n", push, pop, max);
    return 0;
}
