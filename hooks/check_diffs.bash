#!/usr/bin/env bash

shopt -s globstar
./CodeJam/mainCreation.bash

for d in examples/**/diff_*
do
    [[ $d =~ ^(.*)diff_(.*)$ ]]
    # echo ${BASH_REMATCH[0]}
    # echo ${BASH_REMATCH[1]}
    # echo ${BASH_REMATCH[2]}
    file=${BASH_REMATCH[1]}${BASH_REMATCH[2]}
    basefile=${BASH_REMATCH[2]}
    # echo $file
    if [ "$(diff $d <(git diff --no-index CodeJam/$basefile $file))" ]
    then
        echo $d and $file did not match up!
        diff $d <(git diff --no-index CodeJam/$basefile $file)
        exit 1
    else
        echo $d and $file did match up!
    fi
done
exit 0
