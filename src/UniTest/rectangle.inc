/*=============================================================================
 
rectangle.inc

#included in test_Polygon.cpp

Four Nodes forming a rectangle

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

FacePtr f = std::make_shared<Polygon>();
Grid g;
Vector3d v;
Node n;
g.add_node(n); // represents all previous Nodes in the Grid g
        
// lower left corner
v = Vector3d(1.0, 1.0, 5.0);
n = Node(1, v);
g.add_node(n);
f->add_node(1);
        
// lower right corner
v = Vector3d(3.0, 1.0, 5.0);
n = Node(2, v);
g.add_node(n);
f->add_node(2);
        
// upper right corner
v = Vector3d(3.0, 4.0, 5.0);
n = Node(3, v);
g.add_node(n);
f->add_node(3);
        
// upper left corner
v = Vector3d(1.0, 4.0, 5.0);
n = Node(4, v);
g.add_node(n);
f->add_node(4);

//  end rectangle.inc
