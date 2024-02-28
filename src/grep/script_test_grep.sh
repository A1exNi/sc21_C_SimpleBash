#!/bin/bash

#-f и отсутствующий файл для шаблона+
#-f и папка вместо файла для шаблона+
#-f шаблон с несколькими пустыми строками подряд+
#-f шаблон с reg выражением в одной строке+
#-f шаблон с reg выражением в несколько строк+
#-f пустой файл шаблона+
#пустой файл для анализа+
#проверить работу с папкой при помощи * + и в cat тоже
#проверить -f -f+
#проверить -e -e+
#-f c bin+
#проверить поиск |+
# проверить очень длинную строку и + в cat тоже
#разные сочетания -f -e и просто выражение+

s21_grep="./s21_grep"
res_g="result_grep.txt"
res_21="result_s21grep.txt"
args=("" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o"
"-iv" "-ic" "-il" "-in" "-ih" "-is" "-io" "-vc" "-vl" "-vn" "-vh" "-vs" "-vo" "-cl" "-cn" "-ch" "-cs" "-co" "-ln" "-lh" "-ls" "-lo" "-nh" "-ns" "-no" "-hs" "-ho" "-so"
"-ivc" "-ivl" "-ivn" "-ivh" "-ivs" "-ivs" "-ivo" "-icl" "-icn" "-ich" "-ics" "-ico" "-iln" "-ilh" "-ils" "-ilo" "-inh" "-ins" "-ino" "-ihs" "-iho" "-iso" "-vcl" "-vcn")

n=1
echo test$n --------------------
for reg in template/*.txt
do
	for file in test/*.txt
	do
		for arg in ${args[@]}
		do
#			echo $arg $reg $file -----------------------------
			grep -f $reg $arg $file > $res_g
			$s21_grep -f $reg $arg $file > $res_21
			cmp $res_g $res_21
		done
	done
done
((n++))
