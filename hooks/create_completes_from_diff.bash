#!/usr/bin/env bash

shopt -s globstar
./CodeJam/mainCreation.bash

for diff_file in examples/*/*/*/{diff_Main.cpp,diff_Solution.py}
do
    if [ ! -f $diff_file ]
    then
        continue
    fi
    [[ $diff_file =~ ^(.*)/diff_(Main.cpp|Solution.py)$ ]]
    orig_file=${BASH_REMATCH[1]}/${BASH_REMATCH[2]}
    bak_file=${BASH_REMATCH[1]}/${BASH_REMATCH[2]}.bak
    basefile=CodeJam/${BASH_REMATCH[2]}
    patch -o $orig_file.recreated $basefile $diff_file
    if [ "$(diff $orig_file.recreated $orig_file)" ]
    then
        if [ -f $bak_file ]
        then
            echo "There was already a backup file $bak_file in the way, so the process terminated here."
            exit 1
        fi
        mv $orig_file $bak_file
        cp $orig_file.recreated $orig_file
    fi
    rm $orig_file.recreated
done
exit 0
