#!/bin/sh
# set to executable using: chmod 755 example.sh

SRCF=$1
OBJF="${SRCF%.*}.o"
EXEF="${SRCF%.*}"

echo 'compiling' $SRCF '->' $EXEF

gcc -g -Wall -I ../../include -c $SRCF

gcc -o $EXEF $OBJF ../../bin/*.o -lm

rm $OBJF
