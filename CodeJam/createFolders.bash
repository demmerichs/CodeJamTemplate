#!/usr/bin/env bash

TARGET_DIR="$1"
PROBLEM_FOLDERS=("${@:2}")

IFS=$'\n'
DIR="$( cd "$( dirname $0 )" && pwd -P )"

rm -rf $DIR/template_problem_folder

bash $DIR/mainCreation.bash

mkdir $DIR/template_problem_folder
cp $DIR/Main.cpp $DIR/template_problem_folder/Main.cpp
cp $DIR/Solution.py.m4 $DIR/template_problem_folder/Solution.py.m4
touch $DIR/template_problem_folder/sample.txt
touch $DIR/template_problem_folder/result.txt
cp $DIR/interactive_runner.py $DIR/template_problem_folder/interactive_runner.py
cp $DIR/execute.bash $DIR/template_problem_folder/execute.bash
cp $DIR/compare_solutions.bash $DIR/template_problem_folder/compare_solutions.bash
cp $DIR/create_test.py $DIR/template_problem_folder/create_test.py
cp $DIR/sync_lines_after_m4.py $DIR/template_problem_folder/sync_lines_after_m4.py


if [[ $TARGET_DIR = "" ]]
then
    echo You must provide 1 argument and optional folder arguments:
    echo "  First: directory location"
    echo "  Optional: letters/names of problem folders to create!"
    exit
fi

mkdir -p "$TARGET_DIR"
echo "  The following folders get created in "$TARGET_DIR


function make_problem_folder {
  name="$1"
  echo "    $name"
  if [ -d "$TARGET_DIR/${name}" ]
  then
      if [ $name != "template_problem_folder" ] && [ -d "$TARGET_DIR/${name}.bak" ]
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

make_problem_folder template_problem_folder
for problem_folder in ${PROBLEM_FOLDERS[@]}
do
  make_problem_folder ${problem_folder}
done
