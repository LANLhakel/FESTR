#!/usr/bin/env python

# Plotting of 2d data on a uniform Cartesian grid

# Usage: python img.py <datafile> <half/full> <2d/3d>
# Example: python img.py d_0.dat full 2d

# Peter Hakel, LANL XCP-5

# Created on 14 March 2019
# Last modified on 20 August 2021

# Copyright (c) 2019, Triad National Security, LLC.
# All rights reserved.
# Use of this source code is governed by the BSD 3-Clause License.
# See top-level license.txt file for full license text.

#------------------------------------------------------------------------------

import sys
import numpy as np
from numpy import array, transpose
import matplotlib.cm as cm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import
from copy import deepcopy

#------------------------------------------------------------------------------

def read_next_line(f):
    """ read the next nonblank line not starting with ## and return it """
    while (True):
        line = f.readline()
        if line == "":
            print("Error: end of file reached in read_next_line")
            sys.exit()
        line = line.strip()
        fields = line.split()
        if len(line.split()) > 0  and  fields[0] != "##":
            break
    return line

#------------------------------------------------------------------------------

def find_word(f, w):
    """ find string w in file f and return its line """
    while (True):
        line = f.readline()
        if line == "":
            print("Error: end of file reached in find_word")
            sys.exit()
        fields = line.split()
        if (len(fields) > 0  and  fields[1] == w):
            break
    return line

#------------------------------------------------------------------------------

def read_next_value(f, w):
    """ find keyword w in file f, skip its first two words,
        and return the rest joined with inserted spaces """
    str_all = find_word(f, w).split()
    n = len(str_all)
    str_out = ""
    for i in range(2, n):
        if i > 2:
            str_out += " "
        str_out += str_all[i]
    return str_out

#------------------------------------------------------------------------------

# read command line options
narg = len(sys.argv)
if (narg != 4):
    print("Usage: ./img.py <datafile> <half/full> <2d/3d>")
    sys.exit()

fname = str(sys.argv[1])
print("opening file: " + fname)

mode = str(sys.argv[2])
print("mode: " + mode)

plot_type = str(sys.argv[3])
print("type: " + plot_type)

# open the data file and read its header
f = open(fname,'r')

name = read_next_value(f, "name:")
print("name: " + name)

unit = read_next_value(f, "unit:")
print("unit: " + unit)
if unit == "1":
    unit = ""

nx = int(read_next_value(f, "nx:"))
print("nx: " + str(nx))

ny = int(read_next_value(f, "ny:"))
print("ny: " + str(ny))

xmin = float(read_next_value(f, "xmin:"))
print("xmin: " + str(xmin))

xmax = float(read_next_value(f, "xmax:"))
print("xmax: " + str(xmax))
xsize = xmax - xmin

ymin = float(read_next_value(f, "ymin:"))
print("ymin: " + str(ymin))

ymax = float(read_next_value(f, "ymax:"))
print("ymax: " + str(ymax))

zmin = float(read_next_value(f, "vmin:"))
print("zmin: " + str(zmin))

zmax = float(read_next_value(f, "vmax:"))
print("zmax: " + str(zmax))

m = int(read_next_value(f, "m:"))
print("m: " + str(m))

# read the data file and create z-list
find_word(f, "start")
xlst = []
ylst = []
zlst = []
dx = (xmax - xmin) / (nx - 1)
dy = (ymax - ymin) / (ny - 1)
for iy in range(ny):
    x1d = []
    y1d = []
    z1d = []
    y = ymin  +  iy * dy
    for ix in range(nx):
        x = xmin  +  ix * dx
        line = read_next_line(f)
        fields = line.split()
        z = float(fields[0])
        x1d.append(x)
        y1d.append(y)
        z1d.append(z)
    if (mode == "full"):
        xhalf = list(-array(x1d))
        xhalf.reverse()
        x1d = xhalf + x1d
        yhalf = deepcopy(y1d)
        y1d = yhalf + y1d
        zhalf = deepcopy(z1d)
        zhalf.reverse()
        if m % 2 == 1: # (-1)^m = exp(i*m*phi), with phi = PI
            zhalf = [-v for v in zhalf]
        z1d = zhalf + z1d
    xlst.append(x1d)
    ylst.append(y1d)
    zlst.append(z1d)
f.close()

if (mode == "full"):
    xmin = -xmax
    print("New xmin: " + str(xmin))

# convert lists to numpy arrays for plotting;
xarr = array(xlst)
yarr = array(ylst)
zarr = array(zlst)

# make the plot
if (plot_type == "3d"):
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(xarr, yarr, zarr, cmap=cm.coolwarm,
                           linewidth=0, antialiased=False,
                           vmin=zmin, vmax=zmax)
    cbar = fig.colorbar(surf, shrink=0.5, aspect=5)

else:
    fig, ax = plt.subplots(1, 1)
    p = plt.imshow(zarr, interpolation='bilinear', cmap=cm.jet,
                   origin='lower', extent=[xmin,xmax,ymin,ymax],
                   vmin=zmin, vmax=zmax)
    cbar = plt.colorbar()

cbar.set_label(unit, rotation=270, labelpad=20)
ax.set_xlabel('R (cm)')
ax.set_ylabel('Z (cm)')
ax.set_title(name)
plt.show()

