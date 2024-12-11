#include "stdio.h"
int main(void) {	
	long stack[10];
	long stack_size;
	int input;
	long result, op1, op2;
	unsigned long line = 1;
	long nbr = -1;
	stack_size = -1;
	long n;
	for(;;){
		input = getchar();
		n = input - '0';	
		if (n >= 0) {
			if(n <= 9){
				if (stack_size == 9) goto error;
				if (nbr == -1) nbr = 0;
				nbr = nbr * 10 + n;
				continue;
			}    
        }
        if (nbr != -1) {
            stack[++stack_size] = nbr;
            nbr = -1;
        }
		if(input == EOF){
			return 0;
		}	
		else if(input == ' '){
			continue;
		}
		else if(input == '\n'){
			if(stack_size != 0) printf("line %ld: error at \\n\n", line);
			else printf("line %ld: %ld\n", line, stack[0]);						
			line++;
			stack_size = -1;
			continue;
		}
		else if(stack_size < 1){
			goto error;
		}
		result = 0;
		op1 = stack[stack_size-1];
		op2 = stack[stack_size];
		if(input == '+') result = op1 + op2;
		else if(input == '-') result = op1 - op2;
		else if(input == '*') result = op1 * op2;
		else if(input == '/'){
			if(op2 ==0) goto error;
			result = op1 / op2;
		}
		else{
			goto error;
		}
		stack[--stack_size] = result;
		continue;

		error:
		printf("line %ld: error at %d\n",line, input);
		while((input = getchar()) != '\n');
		line++;
		stack_size = -1;		
	}	
}
