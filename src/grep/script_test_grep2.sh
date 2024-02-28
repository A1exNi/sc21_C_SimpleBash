#!/bin/bash

args=("l" "i" "v" "c" "n" "h" "s" "o"
      "li" "lv" "lc" "ln" "lh" "ls" "lo"
      "iv" "ic" "in" "ih" "is" "io"
      "vc" "vn" "vh" "vs" "vo"
      "cn" "ch" "cs" "co"
      "nh" "ns" "no"
      "hs" "ho"
      "so")

for arg in ${args[*]}
do
    echo $arg:=======================================
    grep -$arg 'a' test/test.txt test/test2.txt > grep.txt
    echo --------------------------------------------
    ./s21_grep -$arg 'a' test/test.txt test/test2.txt > s21_grep.txt
    cmp grep.txt s21_grep.txt
done
