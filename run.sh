#!/bin/bash -eux

COMPILER=clang++
EXT=.cpp

BUILD_DIR=build
STD='-std=gnu++17'
WARNING='-Wall -Wextra -fsanitize=address -fno-omit-frame-pointer'
CHECKER=./check.py

TARGET=$1
mkdir -p $BUILD_DIR

eval $COMPILER "$STD" "$WARNING" -o "$BUILD_DIR/$TARGET" "$TARGET$EXT"
$CHECKER "$BUILD_DIR/$TARGET"