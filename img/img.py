# Usage: python img.py <datafile> <title> <unit> <nx> <ny> <xmin> <xmax> <ymin> <ymax>
# Example 1: python img.py Sphere1d-yp_time0_img.dat Intensity unit 5 5 0.1 0.9 0.1 0.9
# Example 2: python img.py SphSym1d-yt_img.dat Intensity unit 1001 1001 -0.4995 0.4995 -0.4995 0.4995

# Created on 30 March 2015
# Last modified on 3 March 2019

# Copyright (c) 2015, Triad National Security, LLC.
# All rights reserved.
# Use of this source code is governed by the BSD 3-Clause License.
# See top-level license.txt file for full license text.

# CODE NAME:  FESTR, Version 0.8 (C15068)
# Classification Review Number: LA-CC-15-045
# Export Control Classification Number (ECCN): EAR99
# B&R Code:  DP1516090

import sys
import numpy as np
from numpy import array, transpose
import matplotlib.cm as cm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

# read command line options
fname = str(sys.argv[1])
print "Opening file: ", fname
main_title = str(sys.argv[2])
print "Title: ", main_title
units = str(sys.argv[3])
print "Units: ", units
nx = int(sys.argv[4])
ny = int(sys.argv[5])
print "nx", nx
print "ny", ny
xmin = float(sys.argv[6])
xmax = float(sys.argv[7])
print "xmin", xmin
print "xmax", xmax
ymin = float(sys.argv[8])
ymax = float(sys.argv[9])
print "ymin", ymin
print "ymax", ymax

# open and read the data file and create z-list
f = open(fname,'r')
zlst = []
for iy in range(ny):
    z1d = []
    for ix in range(nx):
        line = f.readline()
        fields = line.split()
        z = float(fields[2])
        z1d.append(z)
    zlst.append(z1d)
    line = f.readline()
f.close()

# convert z-list to numpy array for plotting;
zarr = array(zlst)

# make the plot
fig, ax = plt.subplots(1, 1)
p = plt.imshow(zarr, interpolation='bilinear', cmap=cm.jet,
                origin='lower', extent=[xmin,xmax,ymin,ymax])
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_title(main_title)
cbar = plt.colorbar()
cbar.set_label(units, rotation=270, labelpad=20)

plt.show()

