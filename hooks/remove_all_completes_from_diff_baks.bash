#!/usr/bin/env bash

shopt -s globstar
./CodeJam/mainCreation.bash

for bak_file in examples/*/*/*/{Main.cpp,Solution.py}.bak
do
    if [ ! -f $bak_file ]
    then
        continue
    fi
    rm $bak_file
done
exit 0
