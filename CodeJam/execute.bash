#!/usr/bin/env bash

set -e

if test -n "$ZSH_VERSION"; then
  PROFILE_SHELL=zsh
elif test -n "$BASH_VERSION"; then
  PROFILE_SHELL=bash
elif test -n "$KSH_VERSION"; then
  PROFILE_SHELL=ksh
elif test -n "$FCEDIT"; then
  PROFILE_SHELL=ksh
elif test -n "$PS3"; then
  PROFILE_SHELL=unknown
else
  PROFILE_SHELL=sh
fi

if [ $PROFILE_SHELL != "bash" ]
then
    echo "The following shell seems to be used ... "$PROFILE_SHELL
    echo "However, it is best tested with bash shells! I wish you the best of luck :)"
else
    echo "Great, you are using bash which is well-tested!"
fi

if [ -z $1 ]
then
    function color {
        "$@" 2> >(sed $'s,.*,\e[31m&\e[m,' 1>&2)
    }
else
    if [ $1 = "PDB" ]
    then
        function color {
            "$@" 2> >(sed $'s,.*,\e[31m&\e[m,' 1>&2)
        }
        m4 --synclines -DLOCAL -DPDB Solution.py.m4 | tail -n +2 | ./sync_lines_after_m4.py > Solution.py
        chmod +x Solution.py
        color ./Solution.py < sample.txt
        exit 0
    else
        color()(set -o pipefail;"$@" 2>/dev/null)
        TEST="True"
    fi
fi

if [[ -f Solution.py.m4 && -f ../template_problem_folder/Solution.py.m4 && ! -z $(diff Solution.py.m4 ../template_problem_folder/Solution.py.m4) ]]
then
    echo "#####################################################################"
    echo "Using Python solution..."
    echo "#####################################################################"

    if [ $TEST ]
    then
        exec="Solution_upload.py"
    else
        exec="Solution.py"
    fi

    m4 --synclines -DLOCAL Solution.py.m4 | tail -n +2 | ./sync_lines_after_m4.py > Solution.py
    m4 --synclines Solution.py.m4 | tail -n +2 | ./sync_lines_after_m4.py > Solution_upload.py
    chmod +x Solution.py
    chmod +x Solution_upload.py

    if [ -f local_testing_tool.py ]
    then
        for i in {0..9}
        do
            color ./interactive_runner.py python3 local_testing_tool.py $i -- ./$exec
        done
    else
        if [ -f result.txt ] && [ -n "$(cat result.txt)" ]
        then
            diffresult="$(echo "$(diff -Z <(time color ./$exec < sample.txt) result.txt)")"
            if [ -z "$diffresult" ]
            then
                :
            else
                echo "Did not produce the expected result! See diff for details:"
                echo "$diffresult"
                exit 1
            fi
        else
            time color ./$exec < sample.txt
        fi
    fi
fi

if [[ -f Main.cpp && -f ../template_problem_folder/Main.cpp && ! -z $(diff Main.cpp ../template_problem_folder/Main.cpp) ]]
then
    echo "#####################################################################"
    echo "Using C++ solution..."
    echo "#####################################################################"

    if [ $TEST ]
    then
        exec="Solution_upload"
        g++-7 Main.cpp -std=c++14 -pthread -O3 -o Solution_upload
    else
        exec="Solution"
        g++-7 Main.cpp -std=c++14 -pthread -O3 -o Solution -DLOCAL
    fi

    if [ -f local_testing_tool.py ]
    then
        for i in {0..9}
        do
            color ./interactive_runner.py python3 local_testing_tool.py $i -- ./$exec
        done
    else
        if [ -f result.txt ] && [ -n "$(cat result.txt)" ]
        then
            diffresult="$(echo "$(diff -Z <(time color ./$exec < sample.txt) result.txt)")"
            if [ -z "$diffresult" ]
            then
                :
            else
                echo "Did not produce the expected result! See diff for details:"
                echo "$diffresult"
                exit 1
            fi
        else
            time color ./$exec < sample.txt
        fi
    fi
fi

if [ ! $TEST ]
then
    ./execute.bash TEST
fi
