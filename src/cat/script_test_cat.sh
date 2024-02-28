#!/bin/bash

#файл начинается с пустой строки+
#файл начинается с 2 пустых строк+
#файл начинается с 3 пустых строк+
#файл состоит из пустых строк+
#файл начанается с текста+
#в файле отсутствуют '\n'+
#в файле есть кириллица+
#в файле есть одна подряд пустая строка+
#в файле есть 2 подряд пустых строки+
#в файле есть 3 подярд пустых строки+
#в файле есть таб+
#фалй заканчивается пустой строкой+
#файл заканчивается 2 пустыми строками+
#файл заканчивается 3 пустыми строками+

#файл состоящий из всех символов+
#длинное название файла+
#большое количество параметров+
#используюутся все параметры+
#используются параметры в разных сочетаниях+
#использование без параметров+
#использование без файла+
#использование без параметров и файла+
#несуществующий файл и несуществующие параметры+
#есл не текстовый файл+
#несолько файлов+
#если передать папку+

#несущ параметр

s21_cat="./s21_cat"
res_c="resut_cat.txt"
res_21="result_s21cat.txt"
args=("-b" "-n" "-s" "-e" "-t" 
"-bn" "-bs" "-be" "-bt" "-ns" "-ne" "-nt" "-se" "-st" "-et" 
"-bns" "-bne" "-bnt" "-bse" "-bst" "-bet" "-bnse" "-bnst" "-bnset")

n=1
#перебор аргументов и тестовых файлов
echo test$n -------------------------
for arg in ${args[@]}
do
	for file in test/*.txt
	do
#echo $arg $file
		cat $arg $file> $res_c
		$s21_cat $arg $file > $res_21
		cmp $res_c $res_21
	done
done
((n++))

#GNU arg
echo test$n -------------------------
for file in test/*.txt
do
    cat -b $file > $res_c
    $s21_cat --number-nonblank $file > $res_21
done
((n++))

echo test$n -------------------------
for file in test/*.txt
do
    cat -n $file > $res_c
    $s21_cat --number $file > $res_21
done
((n++))

echo test$n -------------------------
for file in test/*.txt
do
    cat -s $file > $res_c
    $s21_cat --squeeze-blank $file > $res_21
done
((n++))

#передача папки
echo test$n -------------------------
cat test
$s21_cat test
((n++))

#передача несущ файла
echo test$n -------------------------
cat testttt.txt
$s21_cat testttt.txt
((n++))

#передача папки и сущ файла
echo test$n --------------------
cat test test/test.txt
$s21_cat test test/test.txt
((n++))

#передача несущ и сущ файла
echo test$n --------------------
cat testt.txt test/test.txt
$s21_cat testt.txt test/test.txt
((n++))

#несущ параметры
echo test$n ----------------------
cat -j test/test.txt
$s21_cat -j test/test.txt
((n++))

#длина имен
s="a"
b="a"
c="b"
for ((i=1; i<255; i++))
do
	s=$s$b
done

echo test$n --------------------
cat $s test/test.txt
$s21_cat $s test/test.txt
((n++))

echo test$n --------------------
cat $s$c test/test.txt
$s21_cat $s$c test/test.txt
((n++))

echo test$n --------------------
cat $s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s$c test/test.txt
$s21_cat $s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s$c test/test.txt
((n++))

echo test$n --------------------
cat $s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s$c/$s test/test.txt
$s21_cat $s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s$c/$s test/test.txt
((n++))

echo test$n --------------------
cat $s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s test/test.txt
$s21_cat $s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s test/test.txt
((n++))

echo test$n --------------------
cat $s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s$c test/test.txt
$s21_cat $s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s$c test/test.txt
((n++))

echo test$n --------------------
cat $s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s$c/$s test/test.txt
$s21_cat $s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s/$s$c/$s test/test.txt
((n++))

#несколько файлов
echo test$n --------------------
cat test/test3.txt test/test2.txt > $res_c
$s21_cat test/test3.txt test/test2.txt > $res_21
cmp $res_c $res_21
((n++))

#bin
echo test$n --------------------
cat $s21_cat > $res_c
$s21_cat $s21_cat > $res_21
cmp $res_c $res_21
((n++))

#Неполный длынный аргумент
echo test$n --------------------
cat --number-non test/test.txt
$s21_cat --number-non test/test.txt
((n++))

echo test$n GNU -E -------------------------
echo cat:
cat -e test/test2.txt
echo $s21_cat:
$s21_cat -E test/test2.txt
((n++))

echo test$n GNU -T -------------------------
echo cat:
cat -t test/test2.txt
echo $s21_cat:
$s21_cat -T test/test2.txt
((n++))
