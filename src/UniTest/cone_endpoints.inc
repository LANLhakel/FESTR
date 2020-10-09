/*=============================================================================
 
cone_endpoints.inc

#included in test_Cone.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 22 October 2019
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

// pmh_2019_1031
ConePtr f = std::make_shared<Cone>(4, 3);
Vector3d a(2.0, 0.0, 0.0);
Vector3d b(1.0, 4.0, 0.0);
Node n0;
Node n1(1, a);
Node n2(2, b);
f->add_node(n1.geti());
f->add_node(n2.geti());
Grid g;
g.add_node(n0);
g.add_node(n1);
g.add_node(n2);

double phi = utils::radians(60.0);

//  end cone_endpoints.inc
