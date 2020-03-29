#!/usr/bin/env bash

set -e

if [ -z $1 ]
then
    color()(set -o pipefail;"$@" 2>&1>&3|sed $'s,.*,\e[31m&\e[m,'>&2)3>&1
else
    color()(set -o pipefail;"$@" 2>/dev/null)
fi

if [[ ! -z $(diff Solution.py ../Solution.py) ]]
then
    if [ -f testing_tool.py ]
    then
        color ./interactive_runner.py python testing_tool.py 0 -- ./Solution.py LOCAL
        color ./interactive_runner.py python testing_tool.py 1 -- ./Solution.py LOCAL
        color ./interactive_runner.py python testing_tool.py 2 -- ./Solution.py LOCAL
        color ./interactive_runner.py python testing_tool.py 3 -- ./Solution.py LOCAL
        color ./interactive_runner.py python testing_tool.py 4 -- ./Solution.py LOCAL
        color ./interactive_runner.py python testing_tool.py 5 -- ./Solution.py LOCAL
        color ./interactive_runner.py python testing_tool.py 6 -- ./Solution.py LOCAL
        color ./interactive_runner.py python testing_tool.py 7 -- ./Solution.py LOCAL
        color ./interactive_runner.py python testing_tool.py 8 -- ./Solution.py LOCAL
        color ./interactive_runner.py python testing_tool.py 9 -- ./Solution.py LOCAL
    else
        if [ -f result.txt ] && [ -n "$(cat result.txt)" ]
        then
            diffresult="$(echo "$(diff <(color ./Solution.py LOCAL < sample.txt) result.txt)")"
            if [ -z "$diffresult" ]
            then
                exit 0
            else
                echo "Did not produce the expected result! See diff for details:"
                echo "$diffresult"
                exit 1
            fi
        else
            color ./Solution.py LOCAL < sample.txt
            exit $?
        fi
    fi
else
    g++-7 Main.cpp -std=c++14 -pthread -O3 -o Solution -DLOCAL
    if [ -f testing_tool.py ]
    then
        color ./interactive_runner.py python testing_tool.py 0 -- ./Solution
        color ./interactive_runner.py python testing_tool.py 1 -- ./Solution
        color ./interactive_runner.py python testing_tool.py 2 -- ./Solution
        color ./interactive_runner.py python testing_tool.py 3 -- ./Solution
        color ./interactive_runner.py python testing_tool.py 4 -- ./Solution
        color ./interactive_runner.py python testing_tool.py 5 -- ./Solution
        color ./interactive_runner.py python testing_tool.py 6 -- ./Solution
        color ./interactive_runner.py python testing_tool.py 7 -- ./Solution
        color ./interactive_runner.py python testing_tool.py 8 -- ./Solution
        color ./interactive_runner.py python testing_tool.py 9 -- ./Solution
    else
        if [ -f result.txt ] && [ -n "$(cat result.txt)" ]
        then
            diffresult="$(echo "$(diff <(color ./Solution < sample.txt) result.txt)")"
            if [ -z "$diffresult" ]
            then
                exit 0
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
