/*=============================================================================
 
mesh_cones_vertex.inc

#included in test_Mesh.cpp

Two Zones defined by Cones
pmh_2019_1031

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 30 January 2020
Last modified on 30 January 2020

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
FacePtr f;
ZonePtr z;
Mesh m(2);

// Build Grid g of Nodes n

// Nodes
p = Vector3d(0.0, -0.14125, 0.0);
n = Node(0, p, p);
g.add_node(n);

p = Vector3d(0.0, -0.14, 0.0);
n = Node(1, p, p);
g.add_node(n);

p = Vector3d(0.0, -0.138736, 0.0);
n = Node(2, p, p);
g.add_node(n);

p = Vector3d(0.00346442, -0.141249, 0.0);
n = Node(3, p, p);
g.add_node(n);

p = Vector3d(0.00346442, -0.139983, 0.0);
n = Node(4, p, p);
g.add_node(n);

p = Vector3d(0.00331537, -0.138711, 0.0);
n = Node(5, p, p);
g.add_node(n);

//-----------------------------------------------------------------------------

// lower Zone
z = std::make_shared<Zone>(0);
m.add_zone(z);

// bottom (nearly) disk
f = std::make_shared<Cone>(0, 0);
f->add_node(0);
f->add_node(3);
f->add_neighbor(0, 0);
z->add_face(f);

// outer cylinder
f = std::make_shared<Cone>(0, 1);
f->add_node(3);
f->add_node(4);
f->add_neighbor(0, 0);
z->add_face(f);

// top (nearly) disk
f = std::make_shared<Cone>(0, 2);
f->add_node(4);
f->add_node(1);
f->add_neighbor(1, 0);
z->add_face(f);

//-----------------------------------------------------------------------------

// upper Zone
z = std::make_shared<Zone>(1);
m.add_zone(z);

// bottom (nearly) disk
f = std::make_shared<Cone>(1, 0);
f->add_node(1);
f->add_node(4);
f->add_neighbor(0, 2);
z->add_face(f);

// outer (nearly) cylinder
f = std::make_shared<Cone>(1, 1);
f->add_node(4);
f->add_node(5);
f->add_neighbor(0, 0);
z->add_face(f);

// top (nearly) disk
f = std::make_shared<Cone>(1, 2);
f->add_node(5);
f->add_node(2);
f->add_neighbor(1, 0);
z->add_face(f);

//  end mesh_cones_vertex.inc
