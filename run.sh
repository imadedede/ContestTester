#!/bin/bash -eux

if [ $# == 0 ]; then
    echo "Please Input Your Source File to \$1 without Extention."
    exit
fi

COMPILER=clang++
EXT=.cpp

CURRENT_DIR="$(cd "$(dirname "$0")"; pwd)"
BUILD_DIR="$CURRENT_DIR/build"
STD='-std=gnu++17'
WARNING='-Wall -Wextra -fsanitize=address -fno-omit-frame-pointer'
CHECKER=./check.py

TARGET=$1
mkdir -p "$BUILD_DIR"

eval $COMPILER "$STD" "$WARNING" -o "$BUILD_DIR/$TARGET" "$TARGET$EXT"
$CHECKER "$BUILD_DIR/$TARGET"
