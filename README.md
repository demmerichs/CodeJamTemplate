# CodeJamTemplate
A template for the Google Code Jam Contest and the (now scrapped) Distributed Version. Feel free to fork and share.
Contains code from high ranking contestants condensed together. Sadly I forgot from whom I took the basis of the
Code Jam Template (but most of it I wrote by my own anyway), but the Distributed is tweaked of by the solutions of bmerry submitted DCJ World Finals 2016.

# Usage
## Before Contest
You need to create the contest folder. This can simply be done via:
`/path/to/template/Code\ Jam/createFolders.bash /path/to/contest-folder/eg/2019/Round2 A B C D E`
Relative paths (should) work! You can leave out any of the last letters to get only a subset of folders corresponding to the tasks 1 to 3 for example. Watch out, this script overwrites existing files with the same name, if you provide an existing path (see Todos).

Of course, you should also setup your favorite IDE in advance(see during the contest below). And also do a test run on one of the past problems just to make sure everything runs smoothly on your machine.

## During Contest
Use your favorite IDE. Work on the tasks in their specific folders.

### C++ or Python
The two supported languages by this template. Choose wisely depending on the task. The below steps should work the same either way. Of course, if you deviate, you need to take special care depending on your language selection.

### Non-interactive/Traditional problem
In this case implement your solution in the `Main.cpp` or the `Solution.py` (see the example implementations). The task usually provides a simple example input and the corresponding output. Copy and paste the example input into the `sample.txt` file. Of course you can modify this (helpful for debugging), e.g. by adding more test cases (don't forget to increase the first number T). To test your code on this sample, just execute:
`/path/to/contest-task-folder/eg/A/execute.bash /path/to/contest-task-folder/eg/A/sample.txt`
Again, relative paths work. The output on the terminal should be exactly what is shown on the problem page.

### Interactive problem
Again, work in the corresponding solution file. At the top of the file, set the switch/flag correspondingly, so that the template is aware, that this is an interactive problem. Instead of a sample you can download a file usually called `testing_tool.py` from the problem page. Put this script in your task folder. Then again, you can test your code by executing:
`/path/to/contest-task-folder/eg/A/execute.bash /path/to/contest-task-folder/eg/A/sample.txt`
You could also leave out the last argument, in this case the `execute.bash` detects the existence of `testing_tool.py` and ignores the argument provided.

### General advice
Setup your IDE, so that it works for you and prevents you from doing mistakes during the contest under pressure. You should be able do provide a run configuration, which executes a command with placeholders to have a shortcut for executing the above mentioned lines in a terminal.

E.g. I use Atom as an text editor with Platformio Ide Terminal as one particular package, which lets me have a terminal inside the editor and lets me execute `cd $D; ./execute.bash $F` via a shortcut ($D is placeholder for the directory of the current opened file, and $F for the file itself, so I just switch to `sample.txt` and hit the shortcut, to test my code on traditional problems).

Especially in C++, you should make heavy use of code shortcuts, to avoid spending time on typing and fixing typos. Take a look at the examples in this repo and in the header of the template file, where the definitions of the abbreviations can be found (also in this repo under `tools/abbr.cpp`).

# Todos
- [x] documentation
- [x] example
- [x] implement python template as well (potentially helpful for big ints, string manipulation and other convenient stuff)
- [ ] make the create script more safe so that no present code gets overwritten
- [x] adapt to new Code Jam Interactive Problem structure
- [ ] flush buffer for Interactive Problem (usually not a problem, but good to have just to be safe)
