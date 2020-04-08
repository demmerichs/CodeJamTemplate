#!/usr/bin/env bash

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
cp $DIR/sync_lines_after_m4.py $DIR/template_problem_folder/sync_lines_after_m4.py

TARGET_DIR="$1"
LETTER_1="$2"
LETTER_2="$3"
LETTER_3="$4"
LETTER_4="$5"
LETTER_5="$6"
LETTER_6="$7"

if [[ $TARGET_DIR = "" ]]
then
    echo You must provide 1 argument and optional folder arguments:
    echo "  First: directory location"
    echo "  Optional: letters/names of problem folders to create!"
    exit
fi

mkdir -p "$TARGET_DIR"
cp -r $DIR/template_problem_folder/* "$TARGET_DIR"
echo "  The following folders get created in "$TARGET_DIR

if [[ $LETTER_1 = "" ]]
then
    exit
fi
echo "    "$LETTER_1
if [ -d "$TARGET_DIR/$LETTER_1" ]
then
    if [ -d "$TARGET_DIR/$LETTER_1.bak" ]
    then
        echo "The folders $TARGET_DIR/$LETTER_1 and $TARGET_DIR/$LETTER_1.bak already existed!"
        exit
    else
        cp -r "$TARGET_DIR/$LETTER_1" "$TARGET_DIR/$LETTER_1.bak"
        rm -rf "$TARGET_DIR/$LETTER_1"
    fi
fi
cp -r $DIR/template_problem_folder "$TARGET_DIR/$LETTER_1"

if [[ $LETTER_2 = "" ]]
then
    exit
fi
echo "    "$LETTER_2
if [ -d "$TARGET_DIR/$LETTER_2" ]
then
    if [ -d "$TARGET_DIR/$LETTER_2.bak" ]
    then
        echo "The folders $TARGET_DIR/$LETTER_2 and $TARGET_DIR/$LETTER_2.bak already existed!"
        exit
    else
        cp -r "$TARGET_DIR/$LETTER_2" "$TARGET_DIR/$LETTER_2.bak"
        rm -rf "$TARGET_DIR/$LETTER_2"
    fi
fi
cp -r $DIR/template_problem_folder "$TARGET_DIR/$LETTER_2"

if [[ $LETTER_3 = "" ]]
then
    exit
fi
echo "    "$LETTER_3
if [ -d "$TARGET_DIR/$LETTER_3" ]
then
    if [ -d "$TARGET_DIR/$LETTER_3.bak" ]
    then
        echo "The folders $TARGET_DIR/$LETTER_3 and $TARGET_DIR/$LETTER_3.bak already existed!"
        exit
    else
        cp -r "$TARGET_DIR/$LETTER_3" "$TARGET_DIR/$LETTER_3.bak"
        rm -rf "$TARGET_DIR/$LETTER_3"
    fi
fi
cp -r $DIR/template_problem_folder "$TARGET_DIR/$LETTER_3"

if [[ $LETTER_4 = "" ]]
then
    exit
fi
echo "    "$LETTER_4
if [ -d "$TARGET_DIR/$LETTER_4" ]
then
    if [ -d "$TARGET_DIR/$LETTER_4.bak" ]
    then
        echo "The folders $TARGET_DIR/$LETTER_4 and $TARGET_DIR/$LETTER_4.bak already existed!"
        exit
    else
        cp -r "$TARGET_DIR/$LETTER_4" "$TARGET_DIR/$LETTER_4.bak"
        rm -rf "$TARGET_DIR/$LETTER_4"
    fi
fi
cp -r $DIR/template_problem_folder "$TARGET_DIR/$LETTER_4"

if [[ $LETTER_5 = "" ]]
then
    exit
fi
echo "    "$LETTER_5
if [ -d "$TARGET_DIR/$LETTER_5" ]
then
    if [ -d "$TARGET_DIR/$LETTER_5.bak" ]
    then
        echo "The folders $TARGET_DIR/$LETTER_5 and $TARGET_DIR/$LETTER_5.bak already existed!"
        exit
    else
        cp -r "$TARGET_DIR/$LETTER_5" "$TARGET_DIR/$LETTER_5.bak"
        rm -rf "$TARGET_DIR/$LETTER_5"
    fi
fi
cp -r $DIR/template_problem_folder "$TARGET_DIR/$LETTER_5"

if [[ $LETTER_6 = "" ]]
then
    exit
fi
echo "    "$LETTER_6
if [ -d "$TARGET_DIR/$LETTER_6" ]
then
    if [ -d "$TARGET_DIR/$LETTER_6.bak" ]
    then
        echo "The folders $TARGET_DIR/$LETTER_6 and $TARGET_DIR/$LETTER_6.bak already existed!"
        exit
    else
        cp -r "$TARGET_DIR/$LETTER_6" "$TARGET_DIR/$LETTER_6.bak"
        rm -rf "$TARGET_DIR/$LETTER_6"
    fi
fi
cp -r $DIR/template_problem_folder "$TARGET_DIR/$LETTER_6"
