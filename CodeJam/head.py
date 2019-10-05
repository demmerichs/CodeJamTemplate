#!/usr/bin/env python3

import functools
import numpy as np
import sys
from math import factorial as fac


FLAGS = set()
if len(sys.argv) == 2:
    import pdb; pdb.set_trace()
    assert sys.argv[1] == 'LOCAL'
    FLAGS.add('LOCAL')
# FLAGS.add('DEFAULT_VAL')  #remove comm, to activate default value trigger
# FLAGS.add('IA_MODE')      #remove comm, to activate interactive problem mode
ERROR_WORD = "IMPOSSIBLE"
IA_ERROR_CODE = "ERROR"

# The maintained and empty code template can be found at:
# https://github.com/DavidS3141/CodeJamTemplate
# #region template code
