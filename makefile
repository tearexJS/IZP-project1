CFLAGS=-std=c99 -Wall -Wextra -Werror
pwcheck: pwcheck.o
	gcc -o $@ $^
pwcheck.o: pwcheck.c
	gcc $(CFLAGS) -g -c $^ 
clean: 
	rm -rd *.o pwcheck
