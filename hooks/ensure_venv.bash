#!/usr/bin/env bash

SRC_DIR=$(pwd)

if [ $(basename $SRC_DIR) != "CodeJamTemplate" ]
then
    echo "wrong directory detected for venv creation"
    exit 1
fi

if { conda env list | grep "^gcj "; } >/dev/null 2>&1
then
    :
else
    echo "create venv"
    conda env create -f environment.yml
fi

if [ $CONDA_PREFIX != "gcj" ]
then
    echo "activate venv"
    conda env update -f environment.yml
    source $(conda info --base)/etc/profile.d/conda.sh
    conda activate gcj
fi