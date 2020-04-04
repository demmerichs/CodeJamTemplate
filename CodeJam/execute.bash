#!/usr/bin/env bash

set -e

if [[ -f Solution.py.m4 ]]
then
    m4 --synclines Solution.py.m4 | tail -n +2 | ./sync_lines_after_m4.py > Solution_upload.py
fi

if [ -z $1 ]
then
    color()(set -o pipefail;"$@" 2>&1>&3|sed $'s,.*,\e[31m&\e[m,'>&2)3>&1
else
    if [[ $1 == "PDB" ]]
    then
        color()(set -o pipefail;"$@" 2>&1>&3|sed $'s,.*,\e[31m&\e[m,'>&2)3>&1
        m4 --synclines -DLOCAL -DPDB Solution.py.m4 | tail -n +2 | ./sync_lines_after_m4.py > Solution.py
        chmod +x Solution.py
        color ./Solution.py < sample.txt
        exit 0
    else
        color()(set -o pipefail;"$@" 2>/dev/null)
    fi
fi

if [[ -f Solution.py.m4 && ! -z $(diff Solution.py.m4 ../Solution.py.m4) ]]
then
    echo "#####################################################################"
    echo "Using Python solution..."
    echo "#####################################################################"
    m4 --synclines -DLOCAL Solution.py.m4 | tail -n +2 | ./sync_lines_after_m4.py > Solution.py
    chmod +x Solution.py
    if [ -f local_testing_tool.py ]
    then
        color ./interactive_runner.py python local_testing_tool.py 0 -- ./Solution.py
        color ./interactive_runner.py python local_testing_tool.py 1 -- ./Solution.py
        color ./interactive_runner.py python local_testing_tool.py 2 -- ./Solution.py
        color ./interactive_runner.py python local_testing_tool.py 3 -- ./Solution.py
        color ./interactive_runner.py python local_testing_tool.py 4 -- ./Solution.py
        color ./interactive_runner.py python local_testing_tool.py 5 -- ./Solution.py
        color ./interactive_runner.py python local_testing_tool.py 6 -- ./Solution.py
        color ./interactive_runner.py python local_testing_tool.py 7 -- ./Solution.py
        color ./interactive_runner.py python local_testing_tool.py 8 -- ./Solution.py
        color ./interactive_runner.py python local_testing_tool.py 9 -- ./Solution.py
    else
        if [ -f result.txt ] && [ -n "$(cat result.txt)" ]
        then
            diffresult="$(echo "$(diff <(color ./Solution.py < sample.txt) result.txt)")"
            if [ -z "$diffresult" ]
            then
                :
            else
                echo "Did not produce the expected result! See diff for details:"
                echo "$diffresult"
                exit 1
            fi
        else
            color ./Solution.py < sample.txt
            exit $?
        fi
    fi
fi

if [[ -f Main.cpp && ! -z $(diff Main.cpp ../Main.cpp) ]]
then
    echo "#####################################################################"
    echo "Using C++ solution..."
    echo "#####################################################################"
    g++-7 Main.cpp -std=c++14 -pthread -O3 -o Solution -DLOCAL
    if [ -f local_testing_tool.py ]
    then
        color ./interactive_runner.py python local_testing_tool.py 0 -- ./Solution
        color ./interactive_runner.py python local_testing_tool.py 1 -- ./Solution
        color ./interactive_runner.py python local_testing_tool.py 2 -- ./Solution
        color ./interactive_runner.py python local_testing_tool.py 3 -- ./Solution
        color ./interactive_runner.py python local_testing_tool.py 4 -- ./Solution
        color ./interactive_runner.py python local_testing_tool.py 5 -- ./Solution
        color ./interactive_runner.py python local_testing_tool.py 6 -- ./Solution
        color ./interactive_runner.py python local_testing_tool.py 7 -- ./Solution
        color ./interactive_runner.py python local_testing_tool.py 8 -- ./Solution
        color ./interactive_runner.py python local_testing_tool.py 9 -- ./Solution
    else
        if [ -f result.txt ] && [ -n "$(cat result.txt)" ]
        then
            diffresult="$(echo "$(diff <(color ./Solution < sample.txt) result.txt)")"
            if [ -z "$diffresult" ]
            then
                :
            else
                echo "Did not produce the expected result! See diff for details:"
                echo "$diffresult"
                exit 1
            fi
        else
            color ./Solution < sample.txt
            exit $?
        fi
    fi
fi
