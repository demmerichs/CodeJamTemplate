#!/usr/bin/env bash

examples_readme=examples/README.md
echo "# Implementation of examples" > $examples_readme
echo >> $examples_readme
tree -P 'Main.cpp|Solution.py.m4|diff_Main.cpp|diff_Solution.py.m4' -vf --noreport -I '*~' --charset ascii examples \
    | tail -n +2 \
    | sed -e's/| /  /g' -e 's/    /  /g' -e 's/[|`]-\+/*/g' -e 's:\(* \)\(\(.*/\)\([^/]\+\)\):\1[\4](\2):g' \
    >> $examples_readme

git add $examples_readme
exit 0
