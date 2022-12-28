CC=gcc
FLAGS=-Wall -Werror -Wextra

all: test

clean: 
	rm -f *.o *.a *.css *.html *.gcno *.gcda *.gcov tests s21_math_test.c s21_math.c

s21_math.a: s21_math.o
	ar rc s21_math.a *.o #s21_math.o

s21_math.o: functions/*.c
	#cat functions/*.c >> s21_math.c 
	$(CC) $(FLAGS) -std=c11 -c functions/*.c
	
s21_math_test.o: 
	checkmk s21_math_test.check > s21_math_test.c
	$(CC) $(FLAGS) -c s21_math_test.c

test: s21_math.a s21_math_test.o
	$(CC) $(FLAGS) s21_math_test.o s21_math.a -o tests -lcheck
	./tests

gcov_report: s21_math_test.o
	$(CC) $(FLAGS) -c -fprofile-arcs -ftest-coverage functions/*.c
	$(CC) $(FLAGS) -fprofile-arcs *.o -o tests -lcheck
	./tests
#	gcov -f s21_math.gcda
	gcovr -r . --html --html-details -o coverage_report.html
	rm *.o

cpplint:
	python3 cpplint.py --extensions=c *.c *.h functions/*.c