/*=============================================================================
 
cube_grid.inc

#included in cube.inc, outer_Sphere.inc

Eight Nodes forming a cube of side length == 1; first vertex at the origin
pmh_2014_1215

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 8 December 2014
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

Vector3d p;
Node n;
Grid g;
Zone z;
Face *f;

// Build Grid g of Nodes n

// Nodes for the cube
p = Vector3d(0.0, 0.0, 0.0);
n = Node(0, p, p);
g.add_node(n);

p = Vector3d(0.0, 0.0, 1.0);
n = Node(1, p, p);
g.add_node(n);

p = Vector3d(0.0, 1.0, 0.0);
n = Node(2, p, p);
g.add_node(n);

p = Vector3d(0.0, 1.0, 1.0);
n = Node(3, p, p);
g.add_node(n);

p = Vector3d(1.0, 0.0, 0.0);
n = Node(4, p, p);
g.add_node(n);

p = Vector3d(1.0, 0.0, 1.0);
n = Node(5, p, p);
g.add_node(n);

p = Vector3d(1.0, 1.0, 0.0);
n = Node(6, p, p);
g.add_node(n);

p = Vector3d(1.0, 1.0, 1.0);
n = Node(7, p, p);
g.add_node(n);

// end cube_grid.inc
