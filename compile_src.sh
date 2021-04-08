#!/bin/sh
# set to executable using: chmod 755 example.sh

gcc -g -Wall -c src/*.c
rm include/*
cp src/*.h include/
rm bin/*
mv *.o bin/
