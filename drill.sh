#!/bin/bash -eu
# 過去問をランダムに表示する

files=(./*.cpp)
norma=3
if [ "$#" -eq 1 ]; then
    norma="$1"
fi
echo Solved Problem:"${#files[*]}"
echo Daily Drill:"$norma"

drill=$(shuf -e "${files[@]}" -n $norma)
for f in $drill ; do
    echo "$f"
    code "$f"
done
