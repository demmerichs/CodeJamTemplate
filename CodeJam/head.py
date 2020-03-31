#!/usr/bin/env python3

FLAGS = set()
# FLAGS.add("DEFAULT_VAL")  #remove comm, to activate default value trigger
# FLAGS.add("IA_MODE")      #remove comm, to activate interactive problem mode
ERROR_WORD = "IMPOSSIBLE"
IA_ERROR_CODE = "ERROR"

# The maintained and empty code template can be found at:
# https://github.com/DavidS3141/CodeJamTemplate
# #region template code
import functools as ft  # noqa: E402
import itertools as it  # noqa: E402
import numpy as np  # noqa: E402
import scipy as sp  # noqa: E402
import sys  # noqa: E402
from math import factorial as fac  # noqa: E402
import math  # noqa: E402
