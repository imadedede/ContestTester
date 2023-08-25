#!/bin/bash -eux

TEMPLATE_DIR=template
SOURCE=$1
DIST=$2

while read -r file
do
    EXT=${file##*.}
    cp "$file" "$DIST.$EXT"
done < <(find "$TEMPLATE_DIR" -name "$SOURCE.*")
