/*=============================================================================
 
hexagon.inc

#included in test_Polygon.cpp

Six Nodes forming a hexagon

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 16 December 2014
Last modified on 3 March 2019

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.8 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

Face *f = new Polygon;
Grid g;
Vector3d v;
Node n;
g.add_node(n); // represents all previous Nodes in the Grid g

// Nodes are defined clockwise
double r = 1.0;
double c = r * 0.5;           // cos(60 degrees)
double s = r * sqrt(3.0)/2.0; // sin(60 degrees)
double ox = -2.0;
double oy = 5.0;
Vector3d center(ox, oy, 0.0);

v = Vector3d(c, s, 0.0) + center;
n = Node(1, v);
g.add_node(n);
f->add_node(1);

v = Vector3d(r, 0.0, 0.0) + center;
n = Node(2, v);
g.add_node(n);
f->add_node(2);

v = Vector3d(c, -s, 0.0) + center;
n = Node(3, v);
g.add_node(n);
f->add_node(3);

v = Vector3d(-c, -s, 0.0) + center;
n = Node(4, v);
g.add_node(n);
f->add_node(4);

v = Vector3d(-r, 0.0, 0.0) + center;
n = Node(5, v);
g.add_node(n);
f->add_node(5);

v = Vector3d(-c, s, 0.0) + center;
n = Node(6, v);
g.add_node(n);
f->add_node(6);

// end hexagon.inc
