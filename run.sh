#!/bin/bash -eux

COMPILER=clang++
EXT=.cpp

STD='-std=gnu++17'
WARNING='-Wall -Wextra -fsanitize=address -fno-omit-frame-pointer'
CHECKER=./check.py

TARGET=$1

eval $COMPILER "$STD" "$WARNING" -o "$TARGET" "$TARGET$EXT"
$CHECKER "$TARGET"
