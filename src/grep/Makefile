FLAGS= -Wall -Wextra -Werror -std=c11 -pedantic

all: s21_grep

clean:
	rm -rf s21_grep *.o

chline.o: ../common/chline.c ../common/chline.h
	gcc $(FLAGS) -c ../common/chline.c -o chline.o

chfilename.o: ../common/chfilename.c ../common/chfilename.h
	gcc $(FLAGS) -c ../common/chfilename.c -o chfilename.o

s21_grep.o: s21_grep.c s21_grep.h
	gcc $(FLAGS) -c s21_grep.c -o s21_grep.o

getstr.o: ../common/getstr.c ../common/getstr.h
	gcc $(FLAGS) -c ../common/getstr.c -o getstr.o

s21_grep: s21_grep.o chfilename.o chline.o getstr.o
	gcc $(FLAGS) s21_grep.o chfilename.o chline.o getstr.o -o s21_grep
