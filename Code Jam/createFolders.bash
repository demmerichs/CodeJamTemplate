#/bin/bash!

IFS=$'\n'
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd -P )"

rm -rf $DIR/A
rm -rf $DIR/B
rm -rf $DIR/C
rm -rf $DIR/D
rm -rf $DIR/E

bash $DIR/mainCreation.bash

mkdir $DIR/A
cp $DIR/Main.cpp $DIR/A/Main.cpp
cp $DIR/Solution.py $DIR/A/Solution.py
cp $DIR/sample.txt $DIR/A/sample.txt
cp $DIR/interactive_runner.py $DIR/A/interactive_runner.py
cp $DIR/execute.bash $DIR/A/execute.bash

mkdir $DIR/B
cp $DIR/Main.cpp $DIR/B/Main.cpp
cp $DIR/Solution.py $DIR/B/Solution.py
cp $DIR/sample.txt $DIR/B/sample.txt
cp $DIR/interactive_runner.py $DIR/B/interactive_runner.py
cp $DIR/execute.bash $DIR/B/execute.bash

mkdir $DIR/C
cp $DIR/Main.cpp $DIR/C/Main.cpp
cp $DIR/Solution.py $DIR/C/Solution.py
cp $DIR/sample.txt $DIR/C/sample.txt
cp $DIR/interactive_runner.py $DIR/C/interactive_runner.py
cp $DIR/execute.bash $DIR/C/execute.bash

mkdir $DIR/D
cp $DIR/Main.cpp $DIR/D/Main.cpp
cp $DIR/Solution.py $DIR/D/Solution.py
cp $DIR/sample.txt $DIR/D/sample.txt
cp $DIR/interactive_runner.py $DIR/D/interactive_runner.py
cp $DIR/execute.bash $DIR/D/execute.bash

mkdir $DIR/E
cp $DIR/Main.cpp $DIR/E/Main.cpp
cp $DIR/Solution.py $DIR/E/Solution.py
cp $DIR/sample.txt $DIR/E/sample.txt
cp $DIR/interactive_runner.py $DIR/E/interactive_runner.py
cp $DIR/execute.bash $DIR/E/execute.bash

TARGET_DIR="$1"
LETTER_1="$2"
LETTER_2="$3"
LETTER_3="$4"
LETTER_4="$5"
LETTER_5="$6"

if [[ $TARGET_DIR = "" ]]
then
    echo You must provide 1 argument and optional folder arguments:
    echo "  First: directory location"
    echo "  Optional: letters of problem folders to create!"
    exit
fi

mkdir "$TARGET_DIR"
# mkdir "$TARGET_DIR/Inputs"
cp -r $DIR/A/* "$TARGET_DIR"
echo "  The following folders get created in "$TARGET_DIR

if [[ $LETTER_1 = "" ]]
then
    exit
fi
echo "    "$LETTER_1
cp -r $DIR/$LETTER_1 "$TARGET_DIR"

if [[ $LETTER_2 = "" ]]
then
    exit
fi
echo "    "$LETTER_2
cp -r $DIR/$LETTER_2 "$TARGET_DIR"

if [[ $LETTER_3 = "" ]]
then
    exit
fi
echo "    "$LETTER_3
cp -r $DIR/$LETTER_3 "$TARGET_DIR"

if [[ $LETTER_4 = "" ]]
then
    exit
fi
echo "    "$LETTER_4
cp -r $DIR/$LETTER_4 "$TARGET_DIR"

if [[ $LETTER_5 = "" ]]
then
    exit
fi
echo "    "$LETTER_5
cp -r $DIR/$LETTER_5 "$TARGET_DIR"
