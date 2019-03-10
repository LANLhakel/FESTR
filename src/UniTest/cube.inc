/*=============================================================================
 
cube.inc

#included in test_Zone.cpp

Zone whose outer surfaces form a cube
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

#include "cube_grid.inc"

// Build Faces of the cube and group them to define this Zone
// normal vectors are pointing outward from the cube;
// Polygon surface orientation is encoded in the order of adding Nodes

// front
f = new Polygon(9, 0);
f->add_node(0);
f->add_node(4);
f->add_node(5);
f->add_node(1);
f->add_neighbor(8, 1);
z.add_face(f);

// back
f = new Polygon(9, 1);
f->add_node(2);
f->add_node(3);
f->add_node(7);
f->add_node(6);
f->add_neighbor(8, 2);
z.add_face(f);

// left
f = new Polygon(9, 2);
f->add_node(0);
f->add_node(1);
f->add_node(3);
f->add_node(2);
f->add_neighbor(8, 3);
z.add_face(f);

// right
f = new Polygon(9, 3);
f->add_node(4);
f->add_node(6);
f->add_node(7);
f->add_node(5);
f->add_neighbor(8, 4);
z.add_face(f);

// bottom
f = new Polygon(9, 4);
f->add_node(0);
f->add_node(2);
f->add_node(6);
f->add_node(4);
f->add_neighbor(8, 5);
z.add_face(f);

// top
f = new Polygon(9, 5);
f->add_node(1);
f->add_node(5);
f->add_node(7);
f->add_node(3);
f->add_neighbor(8, 6);
z.add_face(f);

// end cube.inc
