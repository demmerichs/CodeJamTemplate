#!/usr/bin/env bash

shopt -s globstar
./Code\ Jam/mainCreation.bash

for d in examples/*/*/*/{Main.cpp,Solution.py}
do
    if [ ! -f $d ]
    then
        continue
    fi
    [[ $d =~ ^(.*)/(Main.cpp|Solution.py)$ ]]
    output_file=${BASH_REMATCH[1]}/diff_${BASH_REMATCH[2]}
    basefile=${BASH_REMATCH[2]}
    diff Code\ Jam/$basefile $d > $output_file
done
exit 0
