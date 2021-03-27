#!/bin/sh

if [ -d ./bin/ ]; then
    rm -rf ./bin/
fi

mkdir ./bin/
gcc -O3 ./src/main.c -o ./bin/Brainfuck
