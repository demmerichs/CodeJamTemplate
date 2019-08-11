#!/usr/bin/env bash

set -ex

if [[ ! -z $(diff Solution.py ../Solution.py) ]]
then
    if [ -f testing_tool.py ]
    then
        ./interactive_runner.py python testing_tool.py 0 -- ./Solution.py LOCAL
        ./interactive_runner.py python testing_tool.py 1 -- ./Solution.py LOCAL
        ./interactive_runner.py python testing_tool.py 2 -- ./Solution.py LOCAL
        ./interactive_runner.py python testing_tool.py 3 -- ./Solution.py LOCAL
        ./interactive_runner.py python testing_tool.py 4 -- ./Solution.py LOCAL
        ./interactive_runner.py python testing_tool.py 5 -- ./Solution.py LOCAL
        ./interactive_runner.py python testing_tool.py 6 -- ./Solution.py LOCAL
        ./interactive_runner.py python testing_tool.py 7 -- ./Solution.py LOCAL
        ./interactive_runner.py python testing_tool.py 8 -- ./Solution.py LOCAL
        ./interactive_runner.py python testing_tool.py 9 -- ./Solution.py LOCAL
    else
        ./Solution.py LOCAL < $1 > /dev/null
    fi
else
    g++-6 Main.cpp -std=c++14 -pthread -O3 -o Solution -DLOCAL
    if [ -f testing_tool.py ]
    then
        ./interactive_runner.py python testing_tool.py 0 -- ./Solution
        ./interactive_runner.py python testing_tool.py 1 -- ./Solution
        ./interactive_runner.py python testing_tool.py 2 -- ./Solution
        ./interactive_runner.py python testing_tool.py 3 -- ./Solution
        ./interactive_runner.py python testing_tool.py 4 -- ./Solution
        ./interactive_runner.py python testing_tool.py 5 -- ./Solution
        ./interactive_runner.py python testing_tool.py 6 -- ./Solution
        ./interactive_runner.py python testing_tool.py 7 -- ./Solution
        ./interactive_runner.py python testing_tool.py 8 -- ./Solution
        ./interactive_runner.py python testing_tool.py 9 -- ./Solution
    else
        ./Solution < $1 > /dev/null
    fi
fi
