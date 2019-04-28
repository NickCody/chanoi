
hanoi: hanoi.c stack.c iterative.c stack.c
	gcc -std=c99 -Wall -ggdb hanoi.c stack.c iterative.c -o hanoi;

clean: hanoi
	rm hanoi
