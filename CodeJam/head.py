#!/usr/bin/env python3

FLAGS = set()
# FLAGS.add("DEFAULT_VAL_MODE")  # remove comm, to activate default value trigger
DEFAULT_VAL_TRIGGER = lambda result: result is None  # noqa: E731
DEFAULT_VAL = "IMPOSSIBLE"
# FLAGS.add("IA_MODE")  # remove comm, to activate interactive problem mode
IA_ERROR_CODE = "ERROR"

# The maintained and empty code template can be found at:
# https://github.com/demmerichs/CodeJamTemplate
# #region template code
import functools as ft  # noqa: E402,F401
import itertools as it  # noqa: E402,F401
import math  # noqa: E402,F401
import sys  # noqa: E402,F401
import time  # noqa: E402,F401
from fractions import Fraction  # noqa: E402,F401
from math import factorial as fac  # noqa: E402,F401

import numpy as np  # noqa: E402,F401
import scipy as sp  # noqa: E402,F401
