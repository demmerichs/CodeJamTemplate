#/bin/bash!

IFS=$'\n'
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd -P )"

T=$DIR'/../tools'

cat $DIR/head.cpp <(echo) $T/abbr.cpp <(echo) $T/printerTools.cpp <(echo) $T/debugTools.cpp <(echo) $T/selectionTools.cpp <(echo) $T/mathTools.cpp <(echo) $T/algoTools.cpp <(echo) $T/interactiveTools.cpp <(echo) $DIR/tail.cpp > $DIR/Main.cpp
cat $DIR/head.py <(echo) $T/abbr.py <(echo) $T/printerTools.py <(echo) $T/debugTools.py <(echo) $T/parseTools.py <(echo) $T/mathTools.py <(echo) $T/algoTools.py <(echo) $DIR/tail.py > $DIR/Solution.py.m4
