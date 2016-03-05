import sys
import binascii

def printhex(str, start, end):
  h = binascii.b2a_hex(str[start:end])
  for i in range(0, len(h), 2):
    if i%4 == 0 :
        sys.stdout.write('\x20')
    sys.stdout.write('%c%c' %(h[i],h[i+1]))

def printascii(str, start, end):
  for i in range(start, end):
    if str[i] > '\x20' and str[i] <= '~' :
      sys.stdout.write('%c' %(str[i]))
    else:
      sys.stdout.write('.')
  sys.stdout.write('\n')

def hexdump(content):
  m = len(content)
  for i in range(0,m,16):
    print '%08x:' %(i),
    last = min(i+16,m)
    printhex(content, i, last) 
    sys.stdout.write('\x20'*(((16 -last + i)*5)/2 + 4))
    printascii(content, i, last)