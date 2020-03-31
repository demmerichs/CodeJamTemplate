#!/usr/bin/env bash

examples_readme=examples/README.md
echo "# Implementation of examples" > $examples_readme
echo "In this folder you can find example solutions using the template from this repo." >> $examples_readme
echo "The directory structure starts with the year of the contest, then the round" >> $examples_readme
echo "(\`KS\` stands for the Kick Start competition, the rest is Code Jam)." >> $examples_readme
echo "Every solution contains the complete script which can be uploaded to the" >> $examples_readme
echo "CodeJam server (in case of python upload the \`Solution_upload.py\` created" >> $examples_readme
echo "by the [\`execute.bash\`](/CodeJam/execute.bash#L5) script) and a diff compared to the empty template" >> $examples_readme
echo "to get a feeling of how valuable in certain situations this template can be." >> $examples_readme
echo >> $examples_readme
echo "## Links to competition archives" >> $examples_readme
echo "- 2016" >> $examples_readme
echo "  - [Kick Start](https://codingcompetitions.withgoogle.com/kickstart/archive/2016)" >> $examples_readme
echo "  - [Code Jam](https://codingcompetitions.withgoogle.com/codejam/archive/2016)" >> $examples_readme
echo "- 2017" >> $examples_readme
echo "  - [Kick Start](https://codingcompetitions.withgoogle.com/kickstart/archive/2017)" >> $examples_readme
echo "  - [Code Jam](https://codingcompetitions.withgoogle.com/codejam/archive/2017)" >> $examples_readme
echo "- 2018" >> $examples_readme
echo "  - [Kick Start](https://codingcompetitions.withgoogle.com/kickstart/archive/2018)" >> $examples_readme
echo "  - [Code Jam](https://codingcompetitions.withgoogle.com/codejam/archive/2018)" >> $examples_readme
echo "- 2019" >> $examples_readme
echo "  - [Kick Start](https://codingcompetitions.withgoogle.com/kickstart/archive/2019)" >> $examples_readme
echo "  - [Code Jam](https://codingcompetitions.withgoogle.com/codejam/archive/2019)" >> $examples_readme
echo "- 2020" >> $examples_readme
echo "  - [Kick Start](https://codingcompetitions.withgoogle.com/kickstart/archive/2020)" >> $examples_readme
echo "  - [Code Jam](https://codingcompetitions.withgoogle.com/codejam/archive/2020)" >> $examples_readme
echo >> $examples_readme
echo "## Links to solutions using this template inside this repo" >> $examples_readme
echo >> $examples_readme
(cd examples; tree -P 'Main.cpp|Solution.py.m4|diff_Main.cpp|diff_Solution.py.m4' -vf --noreport -I '*~' --charset ascii . \
    | tail -n +2 \
    | sed -e's/| /  /g' -e 's/    /  /g' -e 's/[|`]-\+/*/g' -e 's:\(* \)\(\(.*/\)\([^/]\+\)\):\1[\4](\2):g') \
    >> $examples_readme

git add $examples_readme
exit 0
