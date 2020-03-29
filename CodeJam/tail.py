# #region main
if "IA_MODE" in FLAGS:

    def get_in():
        in_value = cin()
        if in_value == IA_ERROR_CODE:
            quit()
        log("reading value:\t", in_value)
        return in_value

    def out(t):
        log("sending output:\t", t)
        cout(t)


result = ""


def main():
    init()
    nbr_tests = cin()
    for test_id in range(1, 1 + nbr_tests):
        # read input
        readInput()
        # calc result
        calcFunction()
        if "IA_MODE" not in FLAGS:
            # write output
            cout("Case #%d: " % test_id, end=False)
            cerr("Case #%d: " % test_id, end=False)
            if "DEFAULT_VAL" not in FLAGS:
                cout(result)
                cerr(result)
            if "DEFAULT_VAL" in FLAGS:
                if len(result) > 0:
                    cout(len(result))
                    cerr(len(result))
                    for s in result:
                        cout(s)
                        cerr(s)
                else:
                    errorWord = ERROR_WORD
                    cout(errorWord)
                    cerr(errorWord)


# #endregion main

# #endregion template code


def init():
    global result


def readInput():
    global result


#  write to result
def calcFunction():
    global result


if __name__ == "__main__":
    main()
