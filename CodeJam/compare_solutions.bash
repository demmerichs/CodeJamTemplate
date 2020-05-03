#!/usr/bin/env bash

set -e

function color {
    "$@" 2> >(sed $'s,.*,\e[31m&\e[m,' 1>&2)
}

if [ ! -f create_test.py ]
then
    echo "no test creation script \"create_test.py\" was found"
    exit 1
fi

if [[ $3 == "" ]]
then
    echo "You must provide 3 arguments:"
    echo "  First: first executable that runs on test inputs created by \"create_test.py\""
    echo "  Second: second executable to compare against"
    echo "  Third: integer specifying number of test examples to compare"
    exit 1
fi

for i in $(seq 1 $3)
do
    echo "1" > test_sample.txt
    ./create_test.py >> test_sample.txt
    res1="$(color $1 < test_sample.txt)"
    res2="$(color $2 < test_sample.txt)"
    diffresult="$(echo "$(diff -Z <(echo $res1) <(echo $res2))")"
    echo $i
    if [ -z "$diffresult" ]
    then
        :
    else
        echo "Did not produce the same results! The corresponding sample can be found in \"test_sample.txt\". See diff for details:"
        echo "$diffresult"
        exit 1
    fi
done
