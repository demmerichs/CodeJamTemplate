#!/usr/bin/env bash

shopt -s globstar
./CodeJam/mainCreation.bash

rm -rf test_examples/*

for d in examples/**/{Main.cpp,Solution.py.m4}
do
    if [ ! -f $d ]
    then
        continue
    fi
    [[ $d =~ ^examples/(.*)/(.*)/(Main.cpp|Solution.py.m4)$ ]]
    basedir=examples/${BASH_REMATCH[1]}/${BASH_REMATCH[2]}
    unset recreate
    for k in $basedir/{Main.cpp,Solution.py.m4,result.txt,sample.txt,local_testing_tool.py}
    do
        if [ "$(git status -uno -s $k)" ]
        then
            recreate=test_examples/${BASH_REMATCH[1]}
        fi
    done
    if [ -z $recreate ]
    then
        continue
    fi
    ./CodeJam/createFolders.bash $recreate ${BASH_REMATCH[2]}
    rm -rf $recreate/${BASH_REMATCH[2]}.bak
    for k in $basedir/{Main.cpp,Solution.py.m4,result.txt,sample.txt,local_testing_tool.py,create_test.py}
    do
        if [ -f $k ]
        then
            cp $k $recreate/${BASH_REMATCH[2]}/.
        fi
    done
done

output=""
for exec_script in test_examples/**/execute.bash
do
    [[ $exec_script =~ ^test_examples/(.*)/execute.bash$ ]]
    d=test_examples/${BASH_REMATCH[1]}
    if [ ! -d $d ]
    then
        continue
    fi
    if ! [[ $(diff $d/Main.cpp CodeJam/Main.cpp) || $(diff $d/Solution.py.m4 CodeJam/Solution.py.m4) ]]
    then
        continue
    fi
    echo "##########"
    echo "##########  Executing $d ..."
    echo "##########"
    (cd $d; ./execute.bash $1)
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
