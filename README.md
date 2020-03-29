# CodeJamTemplate
A template for the Google Code Jam Contest and the (now scrapped) Distributed Version. Feel free to fork and share.
Contains code from high ranking contestants condensed together. Sadly I forgot from whom I took the basis of the
Code Jam Template (but most of it I wrote by my own anyway), but the Distributed is tweaked of by the solutions of bmerry submitted DCJ World Finals 2016.

# Overview

If you consider using this template for the next CodeJam or Kickstart competitions from Google, and wonder how to get started I recommend the following steps:
- Look for some practice problem or round and follow the below instructions for `Usage` as much or as little as you like, to have a running template base to start experimenting with and understanding the template and getting a general idea of how the template works.
- With the created templates you can skim through them, trying to remember the things you like and forget about the things you dislike.
- To help you focus on my most used features, I provided my solutions to recent competitions using this template in the `examples` folder of this repository with an up-to-date [README](examples/README.md) showing the list and links of implemented solutions and the file endings showing the language used.

# Usage
Disclaimer: I make heavy use of `bash` scripts, which might not work nicely in `zsh` or other shells (not tested, feel free to give feedback). However, all these tools are constructed in such a way, that there should be no interaction with the shell necessary except for the `execute.bash` script during the contest, such that this should be a minor complication compared to the gain during contest time. Please test and when in doubt, use a `bash` shell or avoid the `execute.bash` script.
## Before Contest
You need to create the contest folder. This can simply be done via:

`/path/to/template-repo/CodeJam/createFolders.bash /path/to/contest-folder/eg/2019/Round2 A B C D E`

Relative paths (should) work! You can leave out any of the last letters to get only a subset of folders corresponding to the tasks 1 to 3 for example. Watch out, this script overwrites existing files with the same name, if you provide an existing path (see Todos).

Of course, you should also setup your favorite IDE in advance(see during the contest below). And also do a test run on one of the past problems just to make sure everything runs smoothly on your machine.

## During Contest
Use your favorite IDE. Work on the tasks in their specific folders.

### C++ or Python
The two supported languages by this template. Choose wisely depending on the task. The below steps should work the same either way. Of course, if you deviate, you need to take special care depending on your language selection.

### Non-interactive/Traditional problem
In this case implement your solution in the `Main.cpp` or the `Solution.py.m4` (see the example implementations). The task usually provides a simple example input and the corresponding output. Copy and paste the example input into the `sample.txt` file and the corresponding output into the `result.txt`. Of course you can modify this (helpful for debugging), e.g. by adding more test cases (don't forget to increase the first number T and adding the respective results). To test your code on this sample, just execute:

`/path/to/contest-task-folder/eg/A/execute.bash [TEST|PDB]`

Again, relative paths work. The output on the terminal should be just your error messages when everything was correct (corresponding to the `result.txt`). If there was a difference then this is summarized at the end after all your error messages.

The error messages are piped away when an argument like `TEST` is provided to the script.

The `lpdb()` statements get activated and are usable if `PDB` is provided as argument to the script.

### Interactive problem
Again, work in the corresponding solution file. At the top of the file, set the switch/flag correspondingly, so that the template is aware, that this is an interactive problem. Instead of a sample you can download a file usually called `testing_tool.py` from the problem page. Put this script in your task folder. Then again, you can test your code by executing:

`/path/to/contest-task-folder/eg/A/execute.bash [TEST|PDB]`

In this case the `execute.bash` detects the existence of `testing_tool.py` and ignores the `sample.txt`.

### General advice
Setup your IDE, so that it works for you and prevents you from doing mistakes during the contest under time pressure. You should be able do provide a run configuration, which executes a command with placeholders to have a shortcut for executing the above mentioned lines in a terminal.

E.g. I use Atom as an text editor with Platformio Ide Terminal as one particular package, which lets me have a terminal inside the editor and lets me execute `cd $D; ./execute.bash` via a shortcut ($D is placeholder for the directory of the current opened file, so I can just hit the shortcut, to test my code on problems. Additionally, I have a shortcut for the cleaner output without error messages `cd $D; ./execute.bash TEST` as mentioned above, also for the `PDB` version).

Especially in C++, you should make heavy use of code shortcuts, to avoid spending time on typing and fixing typos. Take a look at the examples in this repo and in the header of the template file, where the definitions of the abbreviations can be found (also in this repo under `tools/abbr.cpp`).

The template makes heavy use of `//#region` and `//#endregion` comments. Hopefully, you are able to configure your IDE to define these comments as custom fold sections. In Atom this can be done with the custom-folds package. Additionally, if you specify all custom regions to be folded upon opening a file, you will have a clean and short view of your file with only the essentials visible, that need modification by you.

# TODOs
- [x] documentation
- [x] example
- [x] implement python template as well (potentially helpful for big ints, string manipulation and other convenient stuff)
- [x] make the create script more safe so that no present code gets overwritten
- [x] adapt to new Code Jam Interactive Problem structure
- [ ] flush buffer for Interactive Problem (usually not a problem, but good to have just to be safe)
- [x] add hooks to pre-commit setup
- [x] make LOCAL mode for python and C++ be resolved in the preprocessor step, so that expansive calls are not made when in evaluation mode
