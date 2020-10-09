/*=============================================================================
 
outer_Sphere.cpp

#included in test_Zone.cpp

Zone whose outer surface is a sphere, inner surfaces form a cube
pmh_2014_1215

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 8 December 2014
Last modified on 27 February 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.9 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

#include <cube_grid.inc>

// Node for the center of the Sphere
p = Vector3d(-1.0, -2.0, -3.0);
n = Node(8, p, p);
g.add_node(n);

// outer Sphere, radius +13.0, oriented outward;
// Sphere surface orientation is encoded in the sign of its radius
SpherePtr s = std::make_shared<Sphere>(8, 0, 13.0, -5.0);
f = s;
s->add_node(n.geti());
z.add_face(f);

// Build Faces of the cube and group them to define this inner Zone
// normal vectors are pointing into the cube
// Polygon surface orientation is encoded in the order of adding Nodes

// front
f = std::make_shared<Polygon>(8, 1);
f->add_node(0);
f->add_node(1);
f->add_node(5);
f->add_node(4);
f->add_neighbor(9, 0);
z.add_face(f);

// back
f = std::make_shared<Polygon>(8, 2);
f->add_node(2);
f->add_node(6);
f->add_node(7);
f->add_node(3);
f->add_neighbor(9, 1);
z.add_face(f);

// left
f = std::make_shared<Polygon>(8, 3);
f->add_node(0);
f->add_node(2);
f->add_node(3);
f->add_node(1);
f->add_neighbor(9, 2);
z.add_face(f);

// right
f = std::make_shared<Polygon>(8, 4);
f->add_node(4);
f->add_node(5);
f->add_node(7);
f->add_node(6);
f->add_neighbor(9, 3);
z.add_face(f);

// bottom
f = std::make_shared<Polygon>(8, 5);
f->add_node(0);
f->add_node(4);
f->add_node(6);
f->add_node(2);
f->add_neighbor(9, 4);
z.add_face(f);

// top
f = std::make_shared<Polygon>(8, 6);
f->add_node(1);
f->add_node(3);
f->add_node(7);
f->add_node(5);
f->add_neighbor(9, 5);
z.add_face(f);

//  end outer_Sphere.cpp
