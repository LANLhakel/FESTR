/*=============================================================================
 
cube_Surface.inc

#included in test_Surface.cpp, test_Zone.cpp

Eight Nodes forming a cube of side length == 1; first vertex at the origin
Six Polygons of square shape form a single Surface

pmh_2014_1215

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 17 December 2014
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

SurfacePtr a = std::make_shared<Surface>(0, 1);
FacePtr q = a;
Vector3d p;
Node n;
Grid g;
FacePtr f;

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

// Build Faces of the cube and group them to define this Surface
// normal vectors are pointing into the cube
// Polygon surface orientation is encoded in the order of adding Nodes
// Polygon "my_zone" here refers to the Surface ID within Surface's zone

// front
f = std::make_shared<Polygon>(0, -1);
f->add_node(0);
f->add_node(1);
f->add_node(5);
f->add_node(4);
f->add_neighbor(1, 0);
a->add_neighbor(1, 0);
a->add_face(f);

// back
f = std::make_shared<Polygon>(1, -1);
f->add_node(2);
f->add_node(6);
f->add_node(7);
f->add_node(3);
f->add_neighbor(1, 1);
a->add_neighbor(1, 1);
a->add_face(f);

// left
f = std::make_shared<Polygon>(2, -1);
f->add_node(0);
f->add_node(2);
f->add_node(3);
f->add_node(1);
f->add_neighbor(1, 2);
a->add_neighbor(1, 2);
a->add_face(f);

// right
f = std::make_shared<Polygon>(3, -1);
f->add_node(4);
f->add_node(5);
f->add_node(7);
f->add_node(6);
f->add_neighbor(1, 3);
a->add_neighbor(1, 3);
a->add_face(f);

// bottom
f = std::make_shared<Polygon>(4, -1);
f->add_node(0);
f->add_node(4);
f->add_node(6);
f->add_node(2);
f->add_neighbor(1, 4);
a->add_neighbor(1, 4);
a->add_face(f);

// top
f = std::make_shared<Polygon>(5, -1);
f->add_node(1);
f->add_node(3);
f->add_node(7);
f->add_node(5);
f->add_neighbor(1, 5);
a->add_neighbor(1, 5);
a->add_face(f);

//  end cube_Surface.inc
