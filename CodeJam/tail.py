# #region main
if "IA_MODE" in FLAGS:

    def get_in():
        in_value = cin()
        if in_value == IA_ERROR_CODE:
            quit()
        llog("reading value:\t", in_value)
        return in_value

    def out(t):
        llog("sending output:\t", t)
        cout(t)


result = ""


def main():
    nbr_tests = cin()
    init()
    for test_id in range(1, 1 + nbr_tests):
        llog()
        llog()
        llog()
        llog()
        llog("`################################################'")
        llog("`################################################'")
        llog("`################################################'")
        llog("`################", test_id, "################'")
        llog("`################################################'")
        llog("`################################################'")
        llog("`################################################'")
        llog()
        llog("============      reading input     ============")
        start_timer()
        readInput()
        stop_timer()
        llog("-----------", get_time(), "secs -----------")
        llog()
        llog("============    doing computation   ============")
        start_timer()
        calcFunction()
        stop_timer()
        llog("-----------", get_time(), "secs -----------")
        llog()

        if "IA_MODE" not in FLAGS:
            # write output
            cout("Case #%d: " % test_id, end=False)
            if "DEFAULT_VAL_MODE" not in FLAGS:
                cout(result)
            if "DEFAULT_VAL_MODE" in FLAGS:
                if DEFAULT_VAL_TRIGGER(result):
                    llog("default val triggered")
                    cout(DEFAULT_VAL)
                else:
                    llog("default val NOT triggered")
                    cout(result)


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
