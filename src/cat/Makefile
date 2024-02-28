FLAGS= -Wall -Wextra -Werror -std=c11 -pedantic

all: s21_cat

clean:
	rm -rf s21_cat *.o

chline.o: ../common/chline.c
	gcc $(FLAGS) -c ../common/chline.c -o chline.o

chfilename.o: ../common/chfilename.c
	gcc $(FLAGS) -c ../common/chfilename.c -o chfilename.o

s21_cat: s21_cat.c chfilename.o chline.o
	gcc $(FLAGS) s21_cat.c chfilename.o  chline.o -o s21_cat
