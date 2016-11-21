#!/bin/sh

TMP_FILE="./lines.txt"

for source in `find . | grep -e [\.][h]$ -e [\.][c][p][p]$`;  do wc -l $source; done > $TMP_FILE;

echo -n "TOTAL LINES : "
gawk '{ sum +=$1 } END { print sum }' $TMP_FILE;

rm -f $TMP_FILE;


 