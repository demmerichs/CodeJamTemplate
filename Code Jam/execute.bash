#!/usr/bin/env bash

if [[ ! -z $(diff Solution.py ../Solution.py) ]]
then
    if [ -f testing_tool.py ]
    then
        ./interactive_runner.py python testing_tool.py 0 -- ./Solution.py
    else
        ./Solution.py < $1 > /dev/null
    fi
else
    g++-6 Main.cpp -std=c++14 -pthread -O3 -o Solution
    if [ -f testing_tool.py ]
    then
        ./interactive_runner.py python testing_tool.py 0 -- ./Solution
    else
        ./Solution < $1 > /dev/null
    fi
fi
