#!/usr/bin/env bash

if [ -f testing_tool.py ]
then
    ./interactive_runner.py python testing_tool.py 0 -- ./Solution
else
    ./Solution < $1 > /dev/null
fi
