#!python

import sys
import zlib
from hexascii import hexdump

narg = len(sys.argv)
filename = sys.argv[1]
fd = open(filename, 'rb')
line = fd.read()
line= zlib.decompress(line)
hexdump(line)

