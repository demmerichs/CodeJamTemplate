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
lastLetter="$2"

if [[ $file = "" || $lastLetter = "" ]]
then
    echo You must provide 2 arguments:
    echo "  First: file location"
    echo "  Second: letter of the last problem!"
    exit
fi

mkdir "$file"
cp -r A "$file"
if [ $lastLetter = "A" ]
then
    exit
fi
cp -r B "$file"
if [ $lastLetter = "B" ]
then
    exit
fi
cp -r C "$file"
if [ $lastLetter = "C" ]
then
    exit
fi
cp -r D "$file"
if [ $lastLetter = "D" ]
then
    exit
fi
cp -r E "$file"
