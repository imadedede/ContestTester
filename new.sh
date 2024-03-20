#!/bin/bash -eu

if [ $# == 0 ]; then
    echo "Please Input Template File Name to \$1."
    exit 1
fi

if [ "$#" == 1  ]; then
    echo "Please Input Your Source File Name to \$2."
    exit 1
fi

TESTCASE_EXT='txt'
CURRENT_DIR="$(cd "$(dirname "$0")"; pwd)"
TEMPLATE_DIR="$CURRENT_DIR/template"
FILE_NAME=${1##*/}
ORIGIN_NAME=${FILE_NAME%.*}
DIST=$2

files=("$TEMPLATE_DIR/$ORIGIN_NAME."*)
for f in "${files[@]}"; do
    EXT=${f##*.}
    DIST_FILE="$DIST.$EXT"
    cp -vn "$f" "$DIST_FILE"

    if [ "$EXT" != "$TESTCASE_EXT" ]; then
        code "$DIST_FILE"
    fi
done
