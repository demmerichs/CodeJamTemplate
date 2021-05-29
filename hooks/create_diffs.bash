#!/usr/bin/env bash

shopt -s globstar
./CodeJam/mainCreation.bash

if [[ -z $1 ]]
then
    echo "You probably do not want to use this script anymore, because it is better to use old diffs to recreate the solution files!"
    echo "If you want to force run this, please provide as argument '-f'!"
    exit 0
fi

if [[ $1 != "-f" ]]
then
    d=$1
    [[ $d =~ ^(.*)/(Main.cpp|Solution.py.m4)$ ]]
    output_file=${BASH_REMATCH[1]}/diff_${BASH_REMATCH[2]}
    basefile=${BASH_REMATCH[2]}
    git diff --no-index CodeJam/$basefile $d > $output_file
    exit 0
fi

for d in examples/**/{Main.cpp,Solution.py.m4}
do
    if [ ! -f $d ]
    then
        continue
    fi
    [[ $d =~ ^(.*)/(Main.cpp|Solution.py.m4)$ ]]
    output_file=${BASH_REMATCH[1]}/diff_${BASH_REMATCH[2]}
    basefile=${BASH_REMATCH[2]}
    git diff --no-index CodeJam/$basefile $d > $output_file
done
exit 0
