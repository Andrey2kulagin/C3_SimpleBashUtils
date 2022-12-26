BUILDDIR= ./

CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: s21_grep 

rebuild: s21_grep 
	

21_grep: 
	$(CC) $(CFLAGS)  s21_grep.c -o $(BUILDDIR) s21_grep 

clean:
	rm -f *.o *.a
	rm -f s21_grep
