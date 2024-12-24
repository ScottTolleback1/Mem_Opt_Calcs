#include "stdio.h"

int main(void) {
    long stack[10];
    long *stack_ptr = stack;  
    int input;
    long result, op1, op2;
    long line = 1;
    long nbr = -1;
    long n;
	long string;

    for (;;) {
        input = getchar();
        n = input - '0';

        if (n >= 0 && n <= 9) { 
            if ((stack_ptr - stack) >= 10) goto error2;  
            if (nbr == -1) nbr = 0;
            nbr = nbr * 10 + n;
            continue;
        }

        if (nbr != -1) {  
            *stack_ptr++ = nbr;
            nbr = -1;
        }

        if (input == EOF) {
            return 0;
        } else if (input == ' ') {
            continue;
        } else if (input == '\n') {
            if ((stack_ptr - stack) != 1) {  
                goto error1;
            } else {
                printf("line %ld: %ld\n", line, stack[0]);
            }
            line++;
            stack_ptr = stack;  
            continue;
        } else if ((stack_ptr - stack) < 2) {  
            goto error2;
        }

        op2 = *--stack_ptr;
        op1 = *--stack_ptr;

        if (input == '+') {
            result = op1 + op2;
        } else if (input == '-') {
            result = op1 - op2;
        } else if (input == '*') {
            result = op1 * op2;
        } else if (input == '/') {
            if (op2 == 0) goto error2;
            result = op1 / op2;
        } else {
            goto error2;  
        }

        *stack_ptr++ = result;  
        continue;

    error1:
		
		string = 0x6E5C;
		goto print;
        
	error2:
		string = input;
		while ((input = getchar()) != '\n');

	print:
		printf("line %ld: error at %s\n", line, (char *) &string);
        line++;
        stack_ptr = stack;  
    }
}
