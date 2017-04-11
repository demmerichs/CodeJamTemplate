rm -rf A
rm -rf B
rm -rf C
rm -rf D
rm -rf E

mkdir A
cp Main.cpp A/Main.cpp
cp sample.txt A/sample.txt

mkdir B
cp Main.cpp B/Main.cpp
cp sample.txt B/sample.txt

mkdir C
cp Main.cpp C/Main.cpp
cp sample.txt C/sample.txt

mkdir D
cp Main.cpp D/Main.cpp
cp sample.txt D/sample.txt

mkdir E
cp Main.cpp E/Main.cpp
cp sample.txt E/sample.txt

file="$1"
let1="$2"
let2="$3"
let3="$4"
let4="$5"
let5="$6"

if [[ $file = "" ]]
then
    echo You must provide 1 argument and optional folder arguments:
    echo "  First: file location"
    echo "  Optional: letter of problem folder to create!"
    exit
fi

mkdir "$file"
echo "  The following folders get created in "$file

if [[ $let1 = "" ]]
then
    exit
fi
echo "    "$let1
cp -r $let1 "$file"

if [[ $let2 = "" ]]
then
    exit
fi
echo "    "$let2
cp -r $let2 "$file"

if [[ $let3 = "" ]]
then
    exit
fi
echo "    "$let3
cp -r $let3 "$file"

if [[ $let4 = "" ]]
then
    exit
fi
echo "    "$let4
cp -r $let4 "$file"

if [[ $let5 = "" ]]
then
    exit
fi
echo "    "$let5
cp -r $let5 "$file"
