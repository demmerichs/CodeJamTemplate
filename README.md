# CodeJamTemplate

A template for the Google Code Jam Contest. Feel free to fork and share.
Contains code from high ranking contestants condensed together. Sadly I forgot from whom I took the basis of the
Code Jam Template (but most of it I wrote by my own anyway).

# Overview

If you consider using this template for the next Code Jam or Kick Start competitions from Google, and wonder how to get started I recommend the following steps:

- Check out a [YouTube video](https://bit.ly/32ET8z0) I made basically going through the steps listed below, in case you prefer watching over reading.
- Look for some practice problem or round and follow the below instructions for [**Usage**](#usage) as much or as little as you like, to have a running template base to start experimenting with, understanding the template and getting a general idea of how the template works.
- With the created templates you can skim through them, trying to remember the things you like and forget about the things you dislike. But to work with this template more efficient than without preparation, please make sure you at least make heavy use of the features described in [**Usage - During Contest - Template Layout**](#template-layout).
- To help you focus on my most used features, I provided my solutions to recent competitions using this template in the [`examples`](examples) folder of this repository with an up-to-date [README](examples) showing the list and links of implemented solutions and the file endings showing the language used.

# Usage

Disclaimer: I make heavy use of `bash` scripts, which might not work nicely in `zsh` or other shells (only tested sporadically, feel free to give feedback). However, all these tools are constructed in such a way, that there should be no interaction with the shell necessary except for the `execute.bash` script during the contest, such that using a `bash` instead of a `zsh` shell should be a minor complication compared to the gain during contest time. Please test and when in doubt, use a `bash` shell or avoid the `execute.bash` script.

## Before Contest

You need to create the contest folder. This can simply be done via:

`/path/to/template-repo/CodeJam/createFolders.bash /path/to/contest-folder/eg/2019/Round2 A B C D E`

Relative paths (should) work! You can leave out any of the last letters to get only a subset of folders corresponding to the tasks 1 to 3 for example. This script copies existing directories with the same name to a `.bak` directory and fails if that directory also exists.

Of course, you should also setup your favorite IDE in advance (see during the contest below). And also do a test run on one or two of the past problems just to make sure everything runs smoothly on your machine. I would suggest doing one traditional and one interactive problem, as they work quite differently.

## During Contest

Use your favorite IDE. Work on the tasks in their specific folders.

### C++ or Python

The two supported languages by this template. Choose wisely depending on the task. The below steps should work the same either way. Of course, if you deviate, you need to take special care depending on your language selection.
Things to consider for the language selection:

- estimated complexity and number of possibly nested loops and conditions in your final program
  - C++ can with the same algorithm design have a large speedup compared to Python
  - this can make the difference in running inside the given time constraints or not
  - rule of thumb: this aspect starts to matter around Round 1 problem 3 and Round 2 upwards possibly everything
- language differences that result in easier code and therefore are less error prone
  - Python has big integers (no upper bound) naturally implemented (watch out not to use numpy arrays, as they convert back to int64)
    - take a look at [examples/2019/Qualification/C/Solution.py.m4](examples/2019/Qualification/C/Solution.py.m4) and the corresponding [problem statement](https://codingcompetitions.withgoogle.com/codejam/round/0000000000051705/000000000008830b)
  - Some problems require you to handle fractions exactly, which can be done quite simple by Python and the `fractions` module.
    - take a look at [examples/2021/Round1A/C/Solution.py.m4](examples/2021/Round1A/C/Solution.py.m4) using fractions and big integers and the corresponding [problem statement](https://codingcompetitions.withgoogle.com/codejam/round/000000000043585d/0000000000754750)
  - Python can do quite easily complex string manipulations and semi-fancy list and fancy numpy indexing operations
- how familiar and fast you are with one language over the other

### Non-interactive/Traditional problem

Implement your solution in the `Main.cpp` or the `Solution.py.m4` (see the example implementations and the section to [**Template Layout**](#template-layout)). The task usually provides a simple example input and the corresponding output. Copy and paste the example input into the `sample.txt` file and the corresponding output into the `result.txt`. Of course you can modify these (helpful for debugging), e.g. by adding more test cases (don't forget to increase the first number `T` and adding the respective results). To test your code on this sample, just execute:

`/path/to/contest-task-folder/eg/A/execute.bash [TEST|PDB]`

Again, relative paths work. The output on the terminal should be just your error/debug messages when everything was correct (corresponding to the `result.txt`). If there was a difference then this is summarized at the end after all your error messages, so you can not miss it.

The error messages are piped away when argument `TEST` is provided to the script. This is helpful when wanting to make sure there are no error messages that you actually print when uploading your solution.

**[ONLY PYTHON]** The `lpdb()` statements get activated and are usable if `PDB` is provided as argument to the script.

### Interactive problem

Again, work in the corresponding solution file. At the top of the file, set the switch/flag correspondingly, so that the template is aware, that this is an interactive problem (see [**Template Layout**](#template-layout)). Instead of a sample you can download a file usually called `local_testing_tool.py` from the problem page. Put this script in your task folder. Then again, you can test your code by executing:

`/path/to/contest-task-folder/eg/A/execute.bash [TEST|PDB]`

In this case the `execute.bash` detects the existence of `local_testing_tool.py` and ignores the `sample.txt`.

### Template Layout

If you open `Main.cpp` or `Solution.py.m4` to work in, and you fold the whole `#region template code` (ideally supported by your IDE as described [below](#general-advice)) you should be left with something like this:

```c++
// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
#define DEFAULT_VAL_TRIGGER result.sz == 0
#define DEFAULT_VAL "IMPOSSIBLE"
// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
#define IA_ERROR_CODE -1
#define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
#define COMM_TYPE ll

// The maintained and empty code template can be found at:
// https://github.com/demmerichs/CodeJamTemplate
//#region template code [...]

namespace task {

void init(){
    cin >> T;
}

void readInput(){
}

// write to COMM_TYPE result
void calcFunction() {
}

} // namespace task
```

What you see (python or C++), is basically a part where you should put your code, which is below the template code region. And at the top are some template control flags which you just comment or uncomment to steer the behavior. We will go through them in just a [second](#control-flags).

#### Code structure

First, let's talk about code organization. Basically, all problems in Code Jam and Kick Start consist of multiple test samples (usually `T=100`, but it is specified on the problem page). This is always the first number in the input and will be read by the template. It also unrolls the necessary `for`-loop for this, so you just need to focus on writing code for a single test sample. However, sometimes it is helpful or even necessary to do some precomputation which depends on the problem, but not on a specific test sample, e.g. it might be necessary to precompute a list of the first 100,000 prime numbers. You do not want to repeat this computation for every of the `T=100` test samples, but do it only once. This is exactly the part of code which you would put into the `init()` function, which will be called before unrolling the loop over the samples.

**[COMPETITION HINT]** In easy problems it is sometimes feasible to precompute (locally or beforehand inside the `init`) with brute force or recursion over every possible input all possible answers, save them and then just return them as needed in the "computation" step.

The other two functions are not that different in execution. But I like to keep the reading input logic and the processing and computation logic separate even in the competition setting and rarely do some preprocessing already inside `readInput()`. If you are not fond if this, you can just ignore one or the other and do all in one place, as they are basically just called consecutively. However, make sure that you parse only a single sample, as the outer `for`-loop over the samples already takes care of calling the `readInput()` function multiple times.

In the end, after the execution of `calcFunction`, you want to make sure you have the result you want to print stored in the variable named `result`. If it has the format of an iterable the print logic of the template has a good chance of handling this in a way that is typical for Code Jam and Kick Start outputs, so just try storing your results in a suitable data structure and hope for the best (there will be most certainly updates to this over the time). If the output is not what you want or need, just write a few lines to make out of your data structure a string and put this in the `result` variable. The printing of the `Case #x:` is done by the template, you do not have access to the current test_id `x` anyway.

This background steering happens all in the `main()` function, which basically reduces to this pseudo code:

```
main:
    nbr_tests <- read integer
    init()
    for test_id in 1...nbr_tests:
        readInput()
        calcFunction()
        print("Case #[test_id]: " + magic_formatting(result))
```

In the case of an interactive problem, this changes a bit, by just not printing `result` anymore. Instead, you should let the interaction happen in the `calcFunction`. In most cases, all your input is interactive in this cases, so the `readInput` function is redundant and I leave it empty. However, there might come a problem along, for which you first need to parse a bulk of numbers in `readInput`, before the actual interaction in `calcFunction` really starts, but again, the template does not force you to use both or one over the other, as long as something solving the task happens in one of them, so just do as you please.

#### Control Flags

Here is a short (language dependent) description of the control flags at the beginning of the template file, which you control by (un-)commenting those lines.

- **DEFAULT_VAL_MODE, DEFAULT_VAL_TRIGGER, DEFAULT_VAL**

  These three control the magic formatting of the `result` data structure. If you activate the _DEFAULT_VAL_MODE_ then there will be some check if your `result` variable carries some data (e.g. integer is non-negative). You can specify this trigger in the _DEFAULT_VAL_TRIGGER_ expression by only using the result variable (all abbreviations and functions work here). If the trigger is signaled, then the _DEFAULT_VAL_ will be just printed, otherwise it will print like usual through the `magic_formatting`. However, remember that you also always can fallback to returning the constructed string in the `result` variable and not using this mechanism.

- **IA_MODE, IA_ERROR_CODE**

  If you are working on an interactive problem, you should activate the _IA_MODE_. This will make sure, that additional error messages are printed visualizing for you, what data is sent between the `local_testing_tool.py` mentioned earlier, and your program. Also, the problem statement will usually describe what the `local_testing_tool.py` will do, when it comes to some kind of error state (probably because you sent data in the wrong way or order). This behavior is usually described as _"It will send a -1 in an error case"_. In this case you would set the _IA_ERROR_CODE_ to -1.

  It is quite important to catch this error code and terminate your program when receiving it, the reason for this being that you are less confused when getting a "WRONG ANSWER" verdict from the judge system. The other case would be, that your program waits indefinitely for another input, but the `local_testing_tool.py` stopped already, and the judge system will report a "TIMELIMIT EXCEEDED" after a while, which will confuse you completely during the contest. For the template code to take care of this, it is important that during _IA_MODE_ you do not use `cin, cout` but `in` (python: `get_in`) and `out(some_value)` on scalar values (eventually calling it multiple times in a row for a list of values).

- **COMM_TYPE** (C++ only)

  C++ is a strongly typed language, that is why you need to specify beforehand what type of data you want to store in the `result` variable. For most problems this will be just an integer (`ll` standing for `long long int`). However, if you want to return something else and hope for the `magic_formatting` or you want to format yourself, you want to change the type of the variable `result` here globally to, e.g. `str`(string) or `v(ll)`(vector of integers).

  Additionally, this type is used in interactive problems for the scalar communication through `in()` and `out(arg)`. So again, you want to set this to `str`, if there is a special type you can not express any other way and need to parse by yourself.

- **XY_NOTATION** (C++ only)

  For some problems you have to deal with some form of grid points or 2D integer vectors. I use the template abbreviation `cell` (integer) or `pnt` (float) for this, which are both based on the `std::complex` data type. They support naturally summation and subtraction, and in some cases the complex product is helpful because of it's geometric interpretation. In this cases, I want to be able to access the two components of the value via `point.x` and `point.y`, so this is exactly what I can do when turning on this flag. However, it happens too often during the competition, that I use `x` for other variables, and then the macro replacement breaks everything, that is why it is turned off by default.

#### Logging & Debugging

First, in C++ you should use `cin` to read data. You should not need `cout`, as the only thing you write to the standard output stream is the result, which is handled by the template. Instead you should write your results to the `result` variable.

Same for Python. As I like the behavior of `cin` in C++ (very helpful for the kind of inputs in these competitions), I emulated it for Python, so I use `val1, val2, val3 = cin(), cin(), cin()` or shorter and faster `val1, val2, val3 = cin(3)` in Python, similar to `cin >> val1 >> val2 >> val3` in C++. And again, you should not use `print` as the printing is done by the template.

And just to mention it again, for interactive problems you should print and parse scalar values (strings, floats, integers) using the `in` and `out` functions provided. As `in` is a keyword in Python, it is named `get_in` in this case. This is important for getting the helpful error messages on the communication provided by the template, and the handling of the interactive error code behind the scenes.

To debug your program, your IDE should support you in making sure you have no syntax or compile problems with your code. Then there are only the runtime and logic errors. Segmentation Faults in C++ should be resolved like you are used to. The logic errors are the hard ones. And especially with the complex problems given, I find it helpful to just dump a lot of numbers into the terminal output and trying to follow my program by hand on paper and comparing notes with the program through the dumped messages and numbers. Here, the template helps a lot, as you can leave these print statements inside the code and push it to the judge system without modification, _if_ you use the right way to dump those messages.

Here you have in both languages the functions `llog`, which takes multiple arguments and prints those to the error stream. So you could do something like `llog(sort(collected_idxs))` and see in red a list of your indexes. And the nice thing is, if you upload this code, this part of the code won't even be compiled or processed, as it is removed by the preprocessor (because Python has no builtin, I use `m4` for this purpose.). So you do not have to worry about adding execution time through the `sort` statement either.

A shortcut `lg` can be used, where `lg(x)` produces the same output as `llog("x", x)` would do.

And I find `assert` very helpful during writing of my code. It helps me find my logic errors faster when testing, as these assertions catch fast the simple mistakes I made when stitching up different code fragments. However, again sometimes you just want to hope for the best and even if an assertion might fire, the code might produce correct results (because your logic for the assertion was the only bug). To avoid this case happening on the judge system, you do not want to have any assertions in this case, they don't have any value. Here the provided solution by the template is `lassert` for both languages, which takes two arguments, the first being a boolean that is asserted, and the second being a string message that is printed. And again, no code written inside that statement is even processed on the judge system, so sorts or complex recursive calls are fine _inside the call_ and won't add to your runtime in the final evaluation.

In Python you should be able to use your normal debugger as mentioned, but if you are a friend of inline `import pdb; pdb.set_trace()` statements, than you can use `lpdb()` as a replacement, which again, will be automatically erased from existence for your uploaded script `Solution_upload.py`.

**[NOTE]** When using your normal debugger and want to have also the error messages and asserts from `llog` and `lassert` then you actually need to run the debugger over the created (when calling `./execute.bash`) `Solution.py` as this is the product of the `m4` preprocessing step.

#### Minor template features

To this I count some logic functions like binary search, golden section search, chinese remainder theorem, range tree, etc.. Not all of them are available in both languages yet, but just have a look at what you can find and know about. And maybe learn about the things you do not know yet :).

However, the most helpful in the C++ domain is probably the abbreviation section, I would really encourage you to look through the whole list, remember the important ones (like `.sz`, `.pb(...)`, `v(...)`, `d(...)`, `sort(all(...))`, `forn`, `fore`, `fornn`, `foreach`, `foreachc`). The less important ones you can look up during the contest when you are fast at locating that section (or just copy and print it beforehand to put it on your desk, or ...).

### General advice

Setup your IDE, so that it works for you and prevents you from doing mistakes during the contest under time pressure. You should be able do provide a run configuration, which executes a command with placeholders to have a shortcut for executing the above mentioned lines in a terminal.

E.g. I use Atom as an text editor with Platformio Ide Terminal as one particular package, which lets me have a terminal inside the editor and lets me execute `cd $D; ./execute.bash` via a shortcut (\$D is placeholder for the directory of the current opened file, so I can just hit the shortcut, to test my code on problems. Additionally, I have a shortcut for the cleaner output without error messages `cd $D; ./execute.bash TEST` as mentioned above, also for the `PDB` version).

Especially in C++, you should make heavy use of code shortcuts, to avoid spending time on typing and fixing typos. Take a look at the examples in this repo and in the header of the template file, where the definitions of the abbreviations can be found (also in this repo under `tools/abbr.cpp`).

The template makes heavy use of `#region` and `#endregion` comments. Hopefully, you are able to configure your IDE to define these comments as custom fold sections. In Atom this can be done with the custom-folds package. Additionally, if you specify all custom regions to be folded upon opening a file, you will have a clean and short view of your file with only the essentials visible, that need modification by you.

# TODOs

- [x] documentation
- [x] example
- [x] implement python template as well (potentially helpful for big ints, string manipulation and other convenient stuff)
- [x] make the create script more safe so that no present code gets overwritten
- [x] adapt to new Code Jam Interactive Problem structure
- [ ] flush buffer for Interactive Problem (usually not a problem, but good to have just to be safe)
- [x] add hooks to pre-commit setup
- [x] make LOCAL mode for python and C++ be resolved in the preprocessor step, so that expansive calls are not made when in evaluation mode
- [ ] implement golden section search for c++
