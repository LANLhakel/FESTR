/*=============================================================================
 
cone.inc

#included in test_Cone.cpp, cone_intercepts.inc

Conical ribbon: a = (2,4); b = (5,8); hypotenuse length = 5

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 14 May 2015
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

Face *f = new Cone(4, 3);
Vector3d a(2.0, 4.0, 0.0);
Vector3d b(5.0, 8.0, 0.0);
Node n0(0, a, 3*a);
Node n1(1, b, 3*b);
f->add_node(n0.geti());
f->add_node(n1.geti());
Grid g;
g.add_node(n0);
g.add_node(n1);
Vector3d c;

// end cone.inc
