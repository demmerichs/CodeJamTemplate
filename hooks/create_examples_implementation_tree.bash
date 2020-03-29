#!/usr/bin/env bash

examples_readme=examples/README.md
echo "# Implementation of examples" > $examples_readme
echo "In this folder you can find example solutions using the template from this repo." >> $examples_readme
echo "The directory structure starts with the year of the contest, then the round" >> $examples_readme
echo "(\`KS\` stands for the Kickstart competition, the rest is CodeJam)." >> $examples_readme
echo "Every solution contains the complete script which can be uploaded to the" >> $examples_readme
echo "CodeJam server (in case of python take the \`Solution_upload.py\` created" >> $examples_readme
echo "by the \`execute.bash\` script) and a diff compared to the empty template" >> $examples_readme
echo "to get a feeling of how valuable in certain situations this template can be." >> $examples_readme
echo >> $examples_readme
tree -P 'Main.cpp|Solution.py.m4|diff_Main.cpp|diff_Solution.py.m4' -vf --noreport -I '*~' --charset ascii examples \
    | tail -n +2 \
    | sed -e's/| /  /g' -e 's/    /  /g' -e 's/[|`]-\+/*/g' -e 's:\(* \)\(\(.*/\)\([^/]\+\)\):\1[\4](\2):g' \
    >> $examples_readme

git add $examples_readme
exit 0
