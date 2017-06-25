#!/usr/bin/python

import sys
import os
from shutil import copyfile

copyfile(sys.argv[1], sys.argv[1].replace('boards.txt', 'boards.txt.bak'))

ifile = open(sys.argv[1])
lines = ifile.readlines()
ifile.close()
ofile = open("/tmp/tmp.txt", 'w')

for line in lines:
    if "teensy36.build.flags.defs" in line:
        ofile.write("teensy36.build.flags.defs=-D__MK66FX1M0__ -DTEENSYDUINO=136")
        for define in sys.argv[2].split(','):
            ofile.write(" %s" % (define))
        ofile.write("\n")
    else:
        ofile.write(line)
ofile.close()

copyfile("/tmp/tmp.txt", sys.argv[1])
