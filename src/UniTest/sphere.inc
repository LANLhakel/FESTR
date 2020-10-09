/*=============================================================================
 
sphere.inc

#included in test_Sphere.cpp

Spherical surface: center = (1,2,3); radius = 13

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 16 December 2014
Last modified on 28 January 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.9 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

SpherePtr s = std::make_shared<Sphere>(4, 3);
FacePtr f = s;
Grid g;
Vector3d c(1.0, 2.0, 3.0); // Sphere center
Node n;
g.add_node(n); // represents all previous Nodes in the Grid g

n = Node(1, c);
g.add_node(n);
f->add_node(1);
s->setr(13.0); // Sphere radius

//  end sphere.inc
