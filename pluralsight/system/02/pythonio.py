#!/usr/bin/python3

import sys

if len(sys.argv) != 3:
  print("usage: python io blocksize blockcount")
  sys.exit(1)

size = int(sys.argv[1])
count = int(sys.argv[2])

buffer = bytearray(size)
f = open("pythonio.out", 'wb')

for i in range(0,count):
  f.write(buffer)

f.close()

