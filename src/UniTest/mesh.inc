/*=============================================================================
 
mesh.inc

#included in test_Mesh.cpp

Two cubes (one of which is cut in half), plus a bounding Sphere
pmh_2014_1219

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 18 December 2014
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
p = Vector3d(0.0, 0.0, 0.0); // also center of the bounding Sphere
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

p = Vector3d(1.0, 0.5, 0.0);
n = Node(8, p, p);
g.add_node(n);

p = Vector3d(1.0, 0.5, 1.0);
n = Node(9, p, p);
g.add_node(n);

p = Vector3d(2.0, 0.0, 0.0);
n = Node(10, p, p);
g.add_node(n);

p = Vector3d(2.0, 0.5, 0.0);
n = Node(11, p, p);
g.add_node(n);

p = Vector3d(2.0, 1.0, 0.0);
n = Node(12, p, p);
g.add_node(n);

p = Vector3d(2.0, 0.0, 1.0);
n = Node(13, p, p);
g.add_node(n);

p = Vector3d(2.0, 0.5, 1.0);
n = Node(14, p, p);
g.add_node(n);

p = Vector3d(2.0, 1.0, 1.0);
n = Node(15, p, p);
g.add_node(n);

//-----------------------------------------------------------------------------

Face *f;
Face *q;
Zone *z;
Sphere *s;
Surface *a;
Mesh m(4);

// Bounding Sphere Zone (outer Face = Sphere)
z = new Zone(0);
m.add_zone(z);
f = s = new Sphere(0, 0);
z->add_face(f);
f->add_node(0); // location of Sphere's center
s->setr(13.0);  // Sphere radius, orientation outward (r is positive)

// Bounding Sphere Zone (inner Face = Surface)
q = a = new Surface(0, 1);
z->add_face(q);

// cube front
f = new Polygon(0, -1);
f->add_node(0);
f->add_node(1);
f->add_node(5);
f->add_node(4);
f->add_neighbor(1,  0);
q->add_neighbor(1,  0);
a->add_face(f);

// cube back
f = new Polygon(1, -1);
f->add_node(2);
f->add_node(6);
f->add_node(7);
f->add_node(3);
f->add_neighbor(1, 1);
q->add_neighbor(1, 1);
a->add_face(f);

// cube left
f = new Polygon(2, -1);
f->add_node(0);
f->add_node(2);
f->add_node(3);
f->add_node(1);
f->add_neighbor(1, 2);
q->add_neighbor(1, 2);
a->add_face(f);

// cube bottom
f = new Polygon(3, -1);
f->add_node(0);
f->add_node(4);
f->add_node(6);
f->add_node(2);
f->add_neighbor(1, 4);
q->add_neighbor(1, 4);
a->add_face(f);

// cube top
f = new Polygon(4, -1);
f->add_node(1);
f->add_node(3);
f->add_node(7);
f->add_node(5);
f->add_neighbor(1, 5);
q->add_neighbor(1, 5);
a->add_face(f);

// front box, front
f = new Polygon(5, -1);
f->add_node(4);
f->add_node(5);
f->add_node(13);
f->add_node(10);
f->add_neighbor(2, 0);
q->add_neighbor(2, 0);
a->add_face(f);

// back box, back
f = new Polygon(6, -1);
f->add_node(6);
f->add_node(12);
f->add_node(15);
f->add_node(7);
f->add_neighbor(3, 1);
q->add_neighbor(3, 1);
a->add_face(f);

// front box, top
f = new Polygon(7, -1);
f->add_node(5);
f->add_node(9);
f->add_node(14);
f->add_node(13);
f->add_neighbor(2, 5);
q->add_neighbor(2, 5);
a->add_face(f);

// front box, right
f = new Polygon(8, -1);
f->add_node(10);
f->add_node(13);
f->add_node(14);
f->add_node(11);
f->add_neighbor(2, 3);
q->add_neighbor(2, 3);
a->add_face(f);

// front box, bottom
f = new Polygon(9, -1);
f->add_node(4);
f->add_node(10);
f->add_node(11);
f->add_node(8);
f->add_neighbor(2, 4);
q->add_neighbor(2, 4);
a->add_face(f);

// back box, top
f = new Polygon(10, -1);
f->add_node(9);
f->add_node(7);
f->add_node(15);
f->add_node(14);
f->add_neighbor(3, 5);
q->add_neighbor(3, 5);
a->add_face(f);

// back box, right
f = new Polygon(11, -1);
f->add_node(11);
f->add_node(14);
f->add_node(15);
f->add_node(12);
f->add_neighbor(3, 3);
q->add_neighbor(3, 3);
a->add_face(f);

// back box, bottom
f = new Polygon(12, -1);
f->add_node(8);
f->add_node(11);
f->add_node(12);
f->add_node(6);
f->add_neighbor(3, 4);
q->add_neighbor(3, 4);
a->add_face(f);

//-----------------------------------------------------------------------------

// cube
z = new Zone(1);
m.add_zone(z);

// front
f = new Polygon(1, 0);
f->add_node(0);
f->add_node(4);
f->add_node(5);
f->add_node(1);
f->add_neighbor(0, 1);
z->add_face(f);

// back
f = new Polygon(1, 1);
f->add_node(2);
f->add_node(3);
f->add_node(7);
f->add_node(6);
f->add_neighbor(0, 1);
z->add_face(f);

// left
f = new Polygon(1, 2);
f->add_node(0);
f->add_node(1);
f->add_node(3);
f->add_node(2);
f->add_neighbor(0, 1);
z->add_face(f);

// right
f = new Polygon(1, 3);
f->add_node(4);
f->add_node(6);
f->add_node(7);
f->add_node(5);
f->add_neighbor(2, 2);
f->add_neighbor(3, 2);
z->add_face(f);

// bottom
f = new Polygon(1, 4);
f->add_node(0);
f->add_node(2);
f->add_node(6);
f->add_node(4);
f->add_neighbor(0, 1);
z->add_face(f);

// top
f = new Polygon(1, 5);
f->add_node(1);
f->add_node(5);
f->add_node(7);
f->add_node(3);
f->add_neighbor(0, 1);
z->add_face(f);

//-----------------------------------------------------------------------------

// front box
z = new Zone(2);
m.add_zone(z);

// front
f = new Polygon(2, 0);
f->add_node(4);
f->add_node(10);
f->add_node(13);
f->add_node(5);
f->add_neighbor(0, 1);
z->add_face(f);

// back
f = new Polygon(2, 1);
f->add_node(8);
f->add_node(9);
f->add_node(14);
f->add_node(11);
f->add_neighbor(3, 0);
z->add_face(f);

// left
f = new Polygon(2, 2);
f->add_node(4);
f->add_node(5);
f->add_node(9);
f->add_node(8);
f->add_neighbor(1, 3);
z->add_face(f);

// right
f = new Polygon(2, 3);
f->add_node(10);
f->add_node(11);
f->add_node(14);
f->add_node(13);
f->add_neighbor(0, 1);
z->add_face(f);

// bottom
f = new Polygon(2, 4);
f->add_node(4);
f->add_node(8);
f->add_node(11);
f->add_node(10);
f->add_neighbor(0, 1);
z->add_face(f);

// top
f = new Polygon(2, 5);
f->add_node(5);
f->add_node(13);
f->add_node(14);
f->add_node(9);
f->add_neighbor(0, 1);
z->add_face(f);

//-----------------------------------------------------------------------------

// back box
z = new Zone(3);
m.add_zone(z);

// front
f = new Polygon(3, 0);
f->add_node(8);
f->add_node(11);
f->add_node(14);
f->add_node(9);
f->add_neighbor(2, 1);
z->add_face(f);

// back
f = new Polygon(3, 1);
f->add_node(6);
f->add_node(7);
f->add_node(15);
f->add_node(12);
f->add_neighbor(0, 1);
z->add_face(f);

// left
f = new Polygon(3, 2);
f->add_node(8);
f->add_node(9);
f->add_node(7);
f->add_node(6);
f->add_neighbor(1, 3);
z->add_face(f);

// right
f = new Polygon(3, 3);
f->add_node(11);
f->add_node(12);
f->add_node(15);
f->add_node(14);
f->add_neighbor(0, 1);
z->add_face(f);

// bottom
f = new Polygon(3, 4);
f->add_node(8);
f->add_node(6);
f->add_node(12);
f->add_node(11);
f->add_neighbor(0, 1);
z->add_face(f);

// top
f = new Polygon(3, 5);
f->add_node(9);
f->add_node(14);
f->add_node(15);
f->add_node(7);
f->add_neighbor(0, 1);
z->add_face(f);

// end mesh.inc
