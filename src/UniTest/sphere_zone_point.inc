/*=============================================================================
 
sphere_zone_point.inc

#included in test_Zone.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 26 February 2020
Last modified on 26 February 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.9 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

Vector3d p;
Node n;
Grid g;
Zone z;
FacePtr f;
SpherePtr s;

// Center Node
p = Vector3d(0.0, 0.0, 0.0);
n = Node(0, p, p);
g.add_node(n);

// Inner Face
s = std::make_shared<Sphere>(4, 0);
f = s;
f->add_node(0);
s->setr(3.0);
z.add_face(f);

// Outer Face
s = std::make_shared<Sphere>(4, 1);
f = s;
f->add_node(0);
s->setr(5.0);
z.add_face(f);

//  end sphere_zone_point.inc
