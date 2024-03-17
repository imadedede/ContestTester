#!/bin/bash -eu

files=(./*.cpp)
echo Solved Problem:"${#files[*]}"

for f in "${files[@]}" ; do
    echo "$f"
    ./run.sh "$f"
    RET=$?
    if [ $RET -ne 0 ] ; then
        exit $RET
    fi
done

echo 'All Programs are Cleared!!!!!!!!!!!!!'
