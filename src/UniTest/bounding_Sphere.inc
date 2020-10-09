/*=============================================================================
 
bounding_Sphere.inc

#included in test_Zone.cpp

Sphere centered at (-1,-2,-3) with radius == +13 (oriented outward)

pmh_2014_1215

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 18 December 2014
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

Zone z;
z.set_id(0);

// Node for the center of the Sphere
p = Vector3d(-1.0, -2.0, -3.0);
n = Node(8, p, p);
g.add_node(n);

auto s = std::make_shared<Sphere>(0, 0, 13.0, -5.0);
f = s;
s->add_node(n.geti());

//  end bounding_Sphere.inc
