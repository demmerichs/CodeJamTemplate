#!/usr/bin/env bash

SRC_DIR=$(pwd)

if [ $(basename $SRC_DIR) != "CodeJamTemplate" ]
then
    echo "wrong directory detected for venv creation"
    exit 1
fi

if [ ! -d $SRC_DIR/.venv ]
then
    echo "create venv"
    python3 -m venv $SRC_DIR/.venv --prompt gcj
fi

if [ -z $VIRTUAL_ENV ]
then
    echo "activate venv"
    source $SRC_DIR/.venv/bin/activate
fi

pip3 install -U -r $SRC_DIR/requirements.txt

exit 0
