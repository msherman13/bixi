#!/usr/bin/python

import sys
import os
from shutil import copyfile

copyfile(sys.argv[2], sys.argv[2].replace('boards.txt', 'boards.txt.bak'))

ifile = open(sys.argv[2])
lines = ifile.readlines()
ifile.close()
ofile = open("/tmp/tmp.txt", 'w')

for line in lines:
    if "teensy36.build.flags.defs" in line:
        ofile.write(line.rstrip('\n') + " " + sys.argv[3].replace(',', ' '))
        ofile.write("\n")
    else:
        ofile.write(line)
ofile.close()

copyfile("/tmp/tmp.txt", sys.argv[2])
