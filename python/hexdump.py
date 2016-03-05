#!python

import sys
from hexascii import hexdump

narg = len(sys.argv)
filename = sys.argv[1]
fd = open(filename,'rb')
line = fd.read()
hexdump(line)

