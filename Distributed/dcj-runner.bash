#/bin/bash!

SOURCE="$1"
[[ $SOURCE =~ ^([^.]*) ]] && SOURCE_NAME=${BASH_REMATCH[1]}
if [[ -e $SOURCE_NAME ]]
then
    cp $SOURCE_NAME $SOURCE_NAME.bak
    rm $SOURCE_NAME
fi

HEAD=$(head -n 1 $SOURCE)
[[ $HEAD =~ ^.*\ \"([^.]*) ]] && TASK_NAME=${BASH_REMATCH[1]}

IFS=$'\n'
DCJ='/Users/David/Documents/Wettbewerbe/Code Jam/dcj_mac_os/dcj.sh'
INPUT_DIR='../Inputs/'
NODES=10

echo \#include \"$INPUT_DIR$TASK_NAME.h\" > $TASK_NAME.h
$DCJ test --source $SOURCE --nodes $NODES

if ! [[ -e $SOURCE_NAME ]]
then
    exit
fi

echo \#include \"$INPUT_DIR$TASK_NAME-2.h\" > $TASK_NAME.h
$DCJ test --source $SOURCE --nodes $NODES

echo \#include \"$INPUT_DIR$TASK_NAME-3.h\" > $TASK_NAME.h
$DCJ test --source $SOURCE --nodes $NODES
