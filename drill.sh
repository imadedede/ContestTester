#!/bin/bash -eu
# 過去問をランダムに表示する

files=(./*.cpp)
norma=3

echo Solved Problem:"${#files[*]}"
echo Daily Drill:"$norma"

drill=$(shuf -e "${files[@]}" -n $norma)
for f in $drill ; do
    echo "$f"
    code "$f"
done
