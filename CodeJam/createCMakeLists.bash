#!/usr/bin/env bash

IFS=$'\n'
DIR="$( cd "$( dirname $0 )" && pwd -P )"

T="$DIR"

PROJECT_NAME="$1"
TARGET_FOLDERS=("${@:2}")

cat <(m4 -DPROJECT_NAME="${PROJECT_NAME}" $T/CMakeLists.txt.m4) > $DIR/CMakeLists.txt

for target_folder in ${TARGET_FOLDERS[@]}
do
  # replace all spaces with '_'
  nn=${target_folder// /_}
  cat <(m4 -DTARGET_NAME="${nn}" -DTARGET_FILE="${target_folder}/Main.cpp" $T/CMakeTarget.m4) >> $DIR/CMakeLists.txt

done

