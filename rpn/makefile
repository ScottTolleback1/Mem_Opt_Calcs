CC      = cc
CFLAGS  = -std=c11 -pedantic -Wall -Werror -g -O3 -funsigned-char
OUT     = a.out
FILE    = rpn

execute: compile
	./a.out < input > output
	diff output correct

compile: clean $(FILE).o malloc.o
	$(CC) $(CFLAGS) -o $(OUT) $(FILE).o malloc.o

$(FILE).o: $(FILE).c
	$(CC) -include wecc.h -c $(FILE).c $(CFLAGS)

malloc.o: malloc.c
	$(CC) -c malloc.c $(CFLAGS) 

assembly: $(FILE).s malloc.s

$(FILE).s: $(FILE).c
	$(CC) -include wecc.h -S $(FILE).c $(CFLAGS)

malloc.s: malloc.c
	$(CC) -S malloc.c $(CFLAGS)

clean:
	rm -f *.s *.o $(OUT) output
