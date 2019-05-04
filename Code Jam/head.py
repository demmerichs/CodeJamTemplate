#!/usr/bin/env python3

import functools
import numpy as np
import sys
from math import factorial as fac


FLAGS = set()
# FLAGS.add('DEFAULT_VAL')  #remove comm, to activate default value trigger
# FLAGS.add('IA_MODE')      #remove comm, to activate interactive problem mode
# FLAGS.add('SUBMIT')       #remove comm, when submitting solution
ERROR_WORD = "IMPOSSIBLE"
IA_ERROR_CODE = -1

# The maintained and empty code template can be found at:
# https://github.com/DavidS3141/CodeJamTemplate
# #region template code
