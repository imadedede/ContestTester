#!/bin/bash -eux

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
