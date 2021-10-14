#!/usr/bin/env python3
import random
import sys
if len(sys.argv) < 2:
    print("Usage: {} string".format(sys.argv[0]))
else:
    s = sys.argv[1]
    for c in s:
        r = random.randint(0, 128)
        print("{} + {}".format((ord(c) - r), r))
