#!/bin/bash

#Test number: 10, name: s21_grep
echo =====================================
grep dictum test/test.txt test/test2.txt > grep.txt
echo -------------------------------------
./s21_grep dictum test/test.txt test/test2.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 11, name: s21_grep
echo =====================================
grep -i O test/test.txt > grep.txt
echo -------------------------------------
./s21_grep -i O test/test.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 12, name: s21_grep
echo =====================================
grep -v s test/test.txt > grep.txt
echo -------------------------------------
./s21_grep -v s test/test.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 13, name: s21_grep
echo =====================================
grep -c s test/test.txt > grep.txt
echo -------------------------------------
./s21_grep -c s test/test.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 14, name: s21_grep
echo =====================================
grep -l s test/test.txt test/test2.txt test/test3.txt > grep.txt
echo -------------------------------------
./s21_grep -l s test/test.txt test/test2.txt test/test3.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 15, name: s21_grep
echo =====================================
grep -n s test/test.txt > grep.txt
echo -------------------------------------
./s21_grep -n s test/test.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 16, name: s21_grep
echo =====================================
grep -o 123 test/test.txt > grep.txt
echo -------------------------------------
./s21_grep -o 123 test/test.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 17, name: s21_grep
echo =====================================
grep -h dictum test/test.txt test/test2.txt > grep.txt
echo -------------------------------------
./s21_grep -h dictum test/test.txt test/test2.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 18, name: s21_grep
echo =====================================
grep grep -s 123123 > grep.txt
echo -------------------------------------
./s21_grep grep -s 123123 > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 19, name: s21_grep
echo =====================================
grep -f test/test.txt test/test2.txt > grep.txt
echo -------------------------------------
./s21_grep -f test/test.txt test/test2.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 20, name: s21_grep
echo =====================================
grep -in dictum test/test.txt > grep.txt
echo -------------------------------------
./s21_grep -in dictum test/test.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 21, name: s21_grep
echo =====================================
grep -cv s test/test.txt > grep.txt
echo -------------------------------------
./s21_grep -cv s test/test.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 22, name: s21_grep
echo =====================================
grep -iv s test/test.txt > grep.txt
echo -------------------------------------
./s21_grep -iv s test/test.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 23, name: s21_grep
echo =====================================
grep -lv s test/test.txt test/test2.txt test/test3.txt > grep.txt
echo -------------------------------------
./s21_grep -lv s test/test.txt test/test2.txt test/test3.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 24, name: s21_grep
echo =====================================
grep -ho dictum test/test.txt test/test2.txt > grep.txt
echo -------------------------------------
./s21_grep -ho dictum test/test.txt test/test2.txt > s21_grep.txt
cmp grep.txt s21_grep.txt

#Test number: 25, name: s21_grep
echo =====================================
grep -nf test/test.txt test/test2.txt > grep.txt
echo -------------------------------------
./s21_grep -nf test/test.txt test/test2.txt > s21_grep.txt
cmp grep.txt s21_grep.txt
