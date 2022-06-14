CC=gcc
FLAGS=-Wall -Werror -Wextra

all: test

clean: 
	rm -f *.o *.a *.css *.html *.gcno *.gcda *.gcov tests s21_string_test.c

s21_string.a: s21_string.o
	ar rc s21_string.a s21_string.o

s21_string.o: s21_string.c
	$(CC) -std=c11 -c s21_string.c
	
s21_string_test.o: 
	checkmk s21_test.check > s21_string_test.c
	$(CC) -c s21_string_test.c

test: s21_string.a s21_string_test.o
	$(CC) $(FLAGS) s21_string_test.o s21_string.a -o tests -lcheck 
	./tests

gcov_report: s21_string_test.o
	$(CC) -c -fprofile-arcs -ftest-coverage s21_string.c
	$(CC) -Wall -fprofile-arcs s21_string_test.o s21_string.o -o tests -lcheck
	./tests
	gcov -f s21_string.gcda
	gcovr -r . --html --html-details -o coverage_report.html
	rm s21_string.o



