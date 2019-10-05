#!/usr/bin/env bash

set -e

if [ -z $2 ]
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
        if [ -f result.txt ]
        then
            if [ -z $(diff <(color ./Solution.py LOCAL < $1) result.txt) ]
            then
                exit 0
            else
                echo "Did not produce the expected result!"
                exit 1
            fi
        else
            color ./Solution.py LOCAL < $1
            exit $?
        fi
    fi
else
    g++-6 Main.cpp -std=c++14 -pthread -O3 -o Solution -DLOCAL
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
        if [ -f result.txt ]
        then
            if [ -z $(diff <(color ./Solution < $1) result.txt) ]
            then
                exit 0
            else
                echo "Did not produce the expected result!"
                exit 1
            fi
        else
            color ./Solution < $1
            exit $?
        fi
    fi
fi
