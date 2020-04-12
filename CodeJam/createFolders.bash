#!/usr/bin/env bash

TARGET_DIR="$1"
PROBLEM_FOLDERS=("${@:2}")

IFS=$'\n'
DIR="$( cd "$( dirname $0 )" && pwd -P )"

if [[ $TARGET_DIR = "" ]]
then
    echo You must provide 1 argument and optional folder arguments:
    echo "  First: directory location"
    echo "  Optional: letters/names of problem folders to create!"
    exit 1
fi

rm -rf $DIR/template_problem_folder

TARGET_ABSOLUTE=$(readlink -f "$TARGET_DIR")
TARGET_BASENAME=$(basename "$TARGET_ABSOLUTE")

bash $DIR/mainCreation.bash
bash $DIR/createCMakeLists.bash $TARGET_BASENAME ${PROBLEM_FOLDERS[@]}

mkdir $DIR/template_problem_folder
cp $DIR/Main.cpp $DIR/template_problem_folder/Main.cpp
cp $DIR/Solution.py.m4 $DIR/template_problem_folder/Solution.py.m4
cp $DIR/CMakeLists.txt $DIR/template_problem_folder/CMakeLists.txt
touch $DIR/template_problem_folder/sample.txt
touch $DIR/template_problem_folder/result.txt
cp $DIR/interactive_runner.py $DIR/template_problem_folder/interactive_runner.py
cp $DIR/execute.bash $DIR/template_problem_folder/execute.bash
cp $DIR/sync_lines_after_m4.py $DIR/template_problem_folder/sync_lines_after_m4.py



mkdir -p "$TARGET_DIR"
cp -r $DIR/template_problem_folder/* "$TARGET_DIR"
echo "  The following folders get created in "$TARGET_DIR


function make_problem_folder {
  name="$1"
  echo "    $name"
  if [ -d "$TARGET_DIR/${name}" ]
  then
      if [ -d "$TARGET_DIR/${name}.bak" ]
      then
          echo "The folders $TARGET_DIR/${name} and $TARGET_DIR/${name}.bak already existed!"
          exit
      else
          cp -r "$TARGET_DIR/${name}" "$TARGET_DIR/${name}.bak"
          rm -rf "$TARGET_DIR/${name}"
      fi
  fi
  cp -r $DIR/template_problem_folder "$TARGET_DIR/${name}"
}


for problem_folder in ${PROBLEM_FOLDERS[@]}
do
  make_problem_folder ${problem_folder}
done

