#/bin/bash!

IFS=$'\n'
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd -P )"

T=$DIR'/../tools'

cat $DIR/head.cpp <(echo) $T/abbr.cpp <(echo) $T/printerTools.cpp <(echo) $T/selectionTools.cpp <(echo) $T/mathTools.cpp <(echo) $T/algoTools.cpp <(echo) $T/parallelTools.cpp <(echo) $T/messageTools.cpp <(echo) $DIR/tail.cpp > $DIR/Main.cpp
