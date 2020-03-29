#!/usr/bin/env bash

shopt -s globstar
./CodeJam/mainCreation.bash

rm -rf test_examples/*

for d in examples/*/*/*/{Main.cpp,Solution.py}
do
    if [ ! -f $d ]
    then
        continue
    fi
    [[ $d =~ ^examples/(.*)/(.*)(_interactive)?/(Main.cpp|Solution.py)$ ]]
    basedir=examples/${BASH_REMATCH[1]}/${BASH_REMATCH[2]}${BASH_REMATCH[3]}
    recreate=test_examples/${BASH_REMATCH[1]}
    mkdir -p $recreate
    ./CodeJam/createFolders.bash $recreate ${BASH_REMATCH[2]}
    for k in $basedir/{Main.cpp,Solution.py,result.txt,sample.txt,testing_tool.py}
    do
        if [ -f $k ]
        then
            cp $k $recreate/${BASH_REMATCH[2]}/.
        fi
    done
done

output=""
for d in test_examples/*/*/*
do
    if [ ! -d $d ]
    then
        continue
    fi
    (cd $d; ./execute.bash TEST)
    runresult=$?
    if [ $runresult != "0" ]
    then
        echo "$d did not work!"
        exit $runresult
    fi
    output="$output"$'\n'"$d"
done
echo
echo -n "Following tests were found and succeeded:"
echo "$output"
exit 0
