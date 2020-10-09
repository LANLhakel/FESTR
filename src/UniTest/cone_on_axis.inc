/*=============================================================================
 
cone_on_axis.inc

#included in test_Cone.cpp, test_Zone.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 25 February 2020
Last modified on 25 February 2020

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
ConePtr s;

// SW Node
p = Vector3d(0.0, 0.0, 0.0);
n = Node(0, p, p);
g.add_node(n);

// SE Node
p = Vector3d(1.0, 0.0, 0.0);
n = Node(1, p, p);
g.add_node(n);

// NE Node
p = Vector3d(1.0, 1.0, 0.0);
n = Node(2, p, p);
g.add_node(n);

// NW Node
p = Vector3d(0.0, 1.0, 0.0);
n = Node(3, p, p);
g.add_node(n);

// Bottom Face
s = std::make_shared<Cone>(4, 0);
f = s;
f->add_node(0);
f->add_node(1);
z.add_face(f);

// Right Face
s = std::make_shared<Cone>(4, 1);
f = s;
f->add_node(1);
f->add_node(2);
z.add_face(f);

// Top Face
s = std::make_shared<Cone>(4, 2);
f = s;
f->add_node(2);
f->add_node(3);
z.add_face(f);

//  end cone_on_axis.inc
