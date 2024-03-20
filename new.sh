#!/bin/bash -eu

if [ $# == 0 ]; then
    echo "Please Input Template File Name to \$1."
    exit
fi

if [ "$#" == 1  ]; then
    echo "Please Input Your Source File Name to \$2."
    exit
fi

CURRENT_DIR="$(cd "$(dirname "$0")"; pwd)"
TEMPLATE_DIR="$CURRENT_DIR/template"
FILE_NAME=${1##*/}
ORIGIN_NAME=${FILE_NAME%.*}
DIST=$2

files=("$TEMPLATE_DIR/$ORIGIN_NAME."*)
for f in "${files[@]}"; do
    EXT=${f##*.}
    cp -vn "$f" "$DIST.$EXT"
done
