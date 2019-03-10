/*=============================================================================
 
sphere0.inc

#included in test_Sphere.cpp

Spherical surface: center = (0,0,0); radius = 5

see pmh_2015_0521 (also for cone0.cpp)

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

FaceID fid(9, 8);
Sphere *s = new Sphere;
Face *f = s;
Grid g;
Vector3d c(0.0, 0.0, 0.0); // Sphere center
Node n;
g.add_node(n); // represents all previous Nodes in the Grid g

n = Node(1, c);
g.add_node(n);
f->add_node(1);
s->setr(5.0); // Sphere radius

// end sphere0.inc
