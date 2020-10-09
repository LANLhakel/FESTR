/*=============================================================================
 
mesh_cones_tiebreaks.inc

#included in test_Mesh.cpp

Three Zones defined by Cones, plus a bounding Sphere
pmh_2019_1031

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 29 October 2019
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

Vector3d p;
Node n;
Grid g;

// Build Grid g of Nodes n

// Nodes
p = Vector3d(0.0, 0.0, 0.0); // center of the bounding Sphere
n = Node(0, p, p);
g.add_node(n);

p = Vector3d(0.0, -1.0e-6, 0.0); // 1e-6 = Cone::MINIMUM_DISTANCE
n = Node(1, p, p);
g.add_node(n);

p = Vector3d(1.0, 0.0, 0.0);
n = Node(2, p, p);
g.add_node(n);

p = Vector3d(2.0, 0.0, 0.0);
n = Node(3, p, p);
g.add_node(n);

p = Vector3d(0.0, -1.0, 0.0);
n = Node(4, p, p);
g.add_node(n);

p = Vector3d(1.0, -1.0, 0.0);
n = Node(5, p, p);
g.add_node(n);

p = Vector3d(2.0, -1.0, 0.0);
n = Node(6, p, p);
g.add_node(n);

p = Vector3d(0.0, 1.0, 0.0);
n = Node(7, p, p);
g.add_node(n);

//-----------------------------------------------------------------------------

FacePtr f;
FacePtr q;
ZonePtr z;
SpherePtr s;
SurfacePtr a;
Mesh m(4);

// Bounding Sphere Zone (outer Face = Sphere)
z = std::make_shared<Zone>(0);
m.add_zone(z);
f = s = std::make_shared<Sphere>(0, 0);
z->add_face(f);
f->add_node(0); // location of Sphere's center
s->setr(100.0); // Sphere radius, orientation outward (r is positive)

// Bounding Sphere Zone (inner Face = Surface)
q = a = std::make_shared<Surface>(0, 1);
z->add_face(q);

// inner Zone's disk bottom
f = std::make_shared<Cone>(0, -1);
f->add_node(5);
f->add_node(4);
f->add_neighbor(1,  0);
q->add_neighbor(1,  0);
a->add_face(f);

// outer Zone's disk bottom
f = std::make_shared<Cone>(1, -1);
f->add_node(6);
f->add_node(5);
f->add_neighbor(2, 0);
q->add_neighbor(2, 0);
a->add_face(f);

// outer Zone's outer cylinder
f = std::make_shared<Cone>(2, -1);
f->add_node(3);
f->add_node(6);
f->add_neighbor(2, 1);
q->add_neighbor(2, 1);
a->add_face(f);

// outer Zone's disk top
f = std::make_shared<Cone>(3, -1);
f->add_node(2);
f->add_node(3);
f->add_neighbor(2, 2);
q->add_neighbor(2, 2);
a->add_face(f);

// top Zone's Cone
f = std::make_shared<Cone>(4, -1);
f->add_node(7);
f->add_node(2);
f->add_neighbor(3, 1);
q->add_neighbor(3, 1);
a->add_face(f);

//-----------------------------------------------------------------------------

// inner Zone
z = std::make_shared<Zone>(1);
m.add_zone(z);

// bottom disk
f = std::make_shared<Cone>(1, 0);
f->add_node(4);
f->add_node(5);
f->add_neighbor(0, 1);
z->add_face(f);

// outer cylinder
f = std::make_shared<Cone>(1, 1);
f->add_node(5);
f->add_node(2);
f->add_neighbor(2, 3);
z->add_face(f);

// top (nearly) disk
f = std::make_shared<Cone>(1, 2);
f->add_node(2);
f->add_node(1);
f->add_neighbor(3, 0);
z->add_face(f);

//-----------------------------------------------------------------------------

// outer Zone
z = std::make_shared<Zone>(2);
m.add_zone(z);

// bottom disk
f = std::make_shared<Cone>(2, 0);
f->add_node(5);
f->add_node(6);
f->add_neighbor(0, 1);
z->add_face(f);

// outer cylinder
f = std::make_shared<Cone>(2, 1);
f->add_node(6);
f->add_node(3);
f->add_neighbor(0, 1);
z->add_face(f);

// top disk
f = std::make_shared<Cone>(2, 2);
f->add_node(3);
f->add_node(2);
f->add_neighbor(0, 1);
z->add_face(f);

// inner cylinder
f = std::make_shared<Cone>(2, 3);
f->add_node(2);
f->add_node(5);
f->add_neighbor(1, 1);
z->add_face(f);

//-----------------------------------------------------------------------------

// top Zone
z = std::make_shared<Zone>(3);
m.add_zone(z);

// bottom (nearly) disk
f = std::make_shared<Cone>(3, 0);
f->add_node(1);
f->add_node(2);
f->add_neighbor(1, 2);
z->add_face(f);

// top Cone
f = std::make_shared<Cone>(3, 1);
f->add_node(2);
f->add_node(7);
f->add_neighbor(0, 1);
z->add_face(f);

//  end mesh_cones_tiebreaks.inc
