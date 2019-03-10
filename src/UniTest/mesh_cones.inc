/*=============================================================================
 
mesh_cones.inc

#included in test_Mesh.cpp

One cylinder, one frustum of a cone, plus a bounding Sphere
pmh_2015_0522

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 22 May 2015
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

// Build Grid g of Nodes n

// Nodes
p = Vector3d(0.0, 1.0, 0.0);
n = Node(0, p, p);
g.add_node(n);

p = Vector3d(0.0, 91.52624423050491, 0.0);
n = Node(1, p, p);
g.add_node(n);

p = Vector3d(5.0, 91.52624423050491, 0.0);
n = Node(2, p, p);
g.add_node(n);

p = Vector3d(5.0, 1.0, 0.0);
n = Node(3, p, p);
g.add_node(n);

p = Vector3d(9.0, 1.0, 0.0);
n = Node(4, p, p);
g.add_node(n);

p = Vector3d(0.0, 0.0, 0.0); // center of the bounding Sphere
n = Node(5, p, p);
g.add_node(n);

//-----------------------------------------------------------------------------

Face *f;
Face *q;
Zone *z;
Sphere *s;
Surface *a;
Mesh m(3);

// Bounding Sphere Zone (outer Face = Sphere)
z = new Zone(0);
m.add_zone(z);
f = s = new Sphere(0, 0);
z->add_face(f);
f->add_node(5); // location of Sphere's center
s->setr(100.0); // Sphere radius, orientation outward (r is positive)

// Bounding Sphere Zone (inner Face = Surface)
q = a = new Surface(0, 1);
z->add_face(q);

// cylinder bottom
f = new Cone(0, -1);
f->add_node(3);
f->add_node(0);
f->add_neighbor(1,  0);
q->add_neighbor(1,  0);
a->add_face(f);

// cylinder top
f = new Cone(1, -1);
f->add_node(1);
f->add_node(2);
f->add_neighbor(1, 2);
q->add_neighbor(1, 2);
a->add_face(f);

// cone bottom
f = new Cone(2, -1);
f->add_node(4);
f->add_node(3);
f->add_neighbor(2, 0);
q->add_neighbor(2, 0);
a->add_face(f);

// cone slanted outer side
f = new Cone(3, -1);
f->add_node(2);
f->add_node(4);
f->add_neighbor(2, 1);
q->add_neighbor(2, 1);
a->add_face(f);

//-----------------------------------------------------------------------------

// cylinder
z = new Zone(1);
m.add_zone(z);

// bottom
f = new Cone(1, 0);
f->add_node(0);
f->add_node(3);
f->add_neighbor(0, 1);
z->add_face(f);

// side
f = new Cone(1, 1);
f->add_node(3);
f->add_node(2);
f->add_neighbor(2, 2);
z->add_face(f);

// top
f = new Cone(1, 2);
f->add_node(2);
f->add_node(1);
f->add_neighbor(0, 1);
z->add_face(f);

//-----------------------------------------------------------------------------

// cone
z = new Zone(2);
m.add_zone(z);

// bottom
f = new Cone(2, 0);
f->add_node(3);
f->add_node(4);
f->add_neighbor(0, 1);
z->add_face(f);

// slanted, outer side
f = new Cone(2, 1);
f->add_node(4);
f->add_node(2);
f->add_neighbor(0, 1);
z->add_face(f);

// vertical, inner side
f = new Cone(2, 2);
f->add_node(2);
f->add_node(3);
f->add_neighbor(1, 1);
z->add_face(f);

// end mesh_cones.inc
