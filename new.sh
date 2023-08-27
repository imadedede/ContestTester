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

while read -r file
do
    EXT=${file##*.}
    cp "$file" "$DIST.$EXT"
done < <(find "$TEMPLATE_DIR" -name "$ORIGIN_NAME.*")
